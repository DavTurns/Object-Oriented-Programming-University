#include "tests.h"

#include "../Repository/MemoryRepo.h"
#include "../Domain/Scooter.h"
#include "../Controller/Controller.h"

#include <assert.h>
#include <iostream>
#include <string>

namespace test {

    void test_repo() {

        auto repo1 = memoryrepo::MemoryRepo<domain::Scooter>();
        shared_ptr<domain::Scooter> scooter_ptr1 = make_shared<domain::Scooter>("sko", "t1", "01.01.2022", "Cluj", 1000,
                                                                                domain::State::parked);
        shared_ptr<domain::Scooter> scooter_ptr2 = make_shared<domain::Scooter>("skt", "t2", "22.11.2022", "Mannheim",
                                                                                1000, domain::State::in_service);
        shared_ptr<domain::Scooter> scooter_ptr3 = make_shared<domain::Scooter>("skr", "t1", "13.12.2022", "Cluj", 1000,
                                                                                domain::State::out_of_use);

        assert(repo1.add(scooter_ptr1));
        assert(repo1.add(scooter_ptr2));
        assert(repo1.add(scooter_ptr3));

        vector<shared_ptr<domain::Scooter>> scooterliste = repo1.find_all();
        assert(scooterliste[0]->get_id() == "sko");
        assert(scooterliste[0]->get_type() == "t1");
        assert(scooterliste[0]->get_first_use_date() == "01.01.2022");

        assert(scooterliste[1]->get_id() == "skt");
        assert(scooterliste[1]->get_type() == "t2");
        assert(scooterliste[1]->get_first_use_date() == "22.11.2022");

        assert(scooterliste[2]->get_id() == "skr");
        assert(scooterliste[2]->get_type() == "t1");
        assert(scooterliste[2]->get_first_use_date() == "13.12.2022");

        assert(repo1.remove("skt") == true);
        scooterliste = repo1.find_all();
        assert(scooterliste.size() == 2);

        shared_ptr<domain::Scooter> scooter_ptr4 = make_shared<domain::Scooter>("skr", "t3", "10.10.2022", "Brasov",
                                                                                1000, domain::State::out_of_use);

        assert(repo1.update(scooter_ptr4) == true);
        scooterliste = repo1.find_all();

        assert(scooterliste.size() == 2);
        assert(scooterliste[1]->get_id() == "skr");
        assert(scooterliste[1]->get_type() == "t3");
        assert(scooterliste[1]->get_first_use_date() == "10.10.2022");

        shared_ptr<domain::Scooter> scooter_ptr5 = make_shared<domain::Scooter>("nnn", "t3", "10.10.2022", "Brasov",
                                                                                1000, domain::State::out_of_use);

        assert(repo1.update(scooter_ptr5) == false);
        cout << "test repo passed\n";
    }

    void test_controller() {

        std::shared_ptr<Repo<domain::Scooter>> repo1 = std::make_shared<memoryrepo::MemoryRepo<domain::Scooter>>();
        std::shared_ptr<Repo<domain::Customer>> repo2 = std::make_shared<memoryrepo::MemoryRepo<domain::Customer>>();
        std::shared_ptr<controller::Controller> ctrl = std::make_shared<controller::Controller>(repo1, repo2);

        //adding scooters
        ctrl->add("ABC", "type1", "2023/12/03", "Brasov, Romania", 12, domain::parked);
        ctrl->add("BSM", "BMW", "2022/04/23", "Florida", 1200, domain::parked);
        ctrl->add("PLK", "Toyota", "2002/02/02", "Rome", 12, domain::out_of_use);
        ctrl->add("ASS", "Toyota", "2012/02/04", "Rome", 9323, domain::parked);

        //adding customers
        ctrl->add_customer("001", "testcustomer1");
        ctrl->add_customer("002", "testcustomer2");

        //login as 001
        ctrl->set_logged_in_customer("001");

        ctrl->reserve_scooter("ABC");
        ctrl->reserve_scooter("BSM");

        //login as 002
        ctrl->set_logged_in_customer("002");

        ctrl->reserve_scooter("ASS");
        ctrl->reserve_scooter("PLK");

        /* current state: customer 001 reserved ABC, BSM
         *                customer 002 reserved ASS tried to reserve PLK but not working because PLK is out of use
         *                logged in as 002
         * */

        vector<shared_ptr<domain::Scooter>> reservedscooters = ctrl->get_reserved_scooters();

        assert(reservedscooters.size() == 1);
        assert((reservedscooters)[0]->get_id() == "ASS");

        ctrl->set_logged_in_customer("001");
        reservedscooters = ctrl->get_reserved_scooters();

        assert(reservedscooters.size() == 2);
        assert((reservedscooters)[0]->get_id() == "ABC");
        assert((reservedscooters)[1]->get_id() == "BSM");

        //ASS cant be used by 001 because its already reserved by 002
        assert(!ctrl->use_scooter("ASS", 1, "newlocation"));
        assert(ctrl->use_scooter("ABC", 1, "newlocation"));

        reservedscooters = ctrl->get_reserved_scooters();
        assert(reservedscooters.size() == 1);
        assert((reservedscooters)[0]->get_id() == "BSM");

        vector<shared_ptr<domain::Scooter>> scooters = ctrl->find_by_km(12, 14);
        assert(scooters[0]->get_id() == "PLK");
        assert(scooters[1]->get_id() == "ABC");

        scooters = ctrl->sort_by_age();
        assert(scooters[0]->get_id() == "PLK");
        assert(scooters[1]->get_id() == "ASS");
        assert(scooters[2]->get_id() == "BSM");
        assert(scooters[3]->get_id() == "ABC");

        scooters = ctrl->find_by_location("Florida");
        assert(scooters[0]->get_id() == "BSM");

        scooters = ctrl->find_by_age("2023");
        assert(scooters[0]->get_id() == "ABC");

        assert(ctrl->remove("BSM"));

        //BSM will be also removed from the list of reserved scooters from customer 001
        reservedscooters = ctrl->get_reserved_scooters();
        assert(reservedscooters.size() == 0);

        assert(ctrl->remove_customer("002"));

        scooters = ctrl->get_all_scooters();

        //assert that scooter ASS, which was before reserved by 002 which is now deleted, is now parked
        for (auto scooter: scooters)
            if (scooter->get_id() == "ASS") assert(scooter->get_state() == domain::parked);

        cout << "test controller passed\n\n";
    }
}
