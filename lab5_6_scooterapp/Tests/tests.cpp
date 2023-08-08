

#include "tests.h"

#include "../Repository/MemoryRepo.h"
#include "../Domain/Scooter.h"
#include "../Controller/Controller.h"

#include <assert.h>
#include <iostream>
#include <string>

namespace test {

    void test_repo(){

        auto repo1 = memoryrepo::MemoryRepo<domain::Scooter>();
        shared_ptr<domain::Scooter> scooter_ptr1 = make_shared<domain::Scooter>("sko", "t1", "01.01.2022", "Cluj", 1000, domain::State::parked);
        shared_ptr<domain::Scooter> scooter_ptr2 = make_shared<domain::Scooter>("skt", "t2", "22.11.2022", "Mannheim", 1000, domain::State::in_service);
        shared_ptr<domain::Scooter> scooter_ptr3 = make_shared<domain::Scooter>("skr", "t1", "13.12.2022", "Cluj", 1000, domain::State::out_of_use);

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

        shared_ptr<domain::Scooter> scooter_ptr4 = make_shared<domain::Scooter>("skr", "t3", "10.10.2022", "Brasov", 1000, domain::State::out_of_use);

        assert(repo1.update(scooter_ptr4) == true);
        scooterliste = repo1.find_all();

        assert(scooterliste.size() == 2);
        assert(scooterliste[1]->get_id() == "skr");
        assert(scooterliste[1]->get_type() == "t3");
        assert(scooterliste[1]->get_first_use_date() == "10.10.2022");

        shared_ptr<domain::Scooter> scooter_ptr5 = make_shared<domain::Scooter>("nnn", "t3", "10.10.2022", "Brasov", 1000, domain::State::out_of_use);

        assert(repo1.update(scooter_ptr5) == false);
        cout << "test_repo passed\n";
    }

    void test_controller(){
        std::shared_ptr<Repo<domain::Scooter>> repo1 = std::make_shared<memoryrepo::MemoryRepo<domain::Scooter>>();
        std::shared_ptr<Repo<domain::Customer>> repo2 = std::make_shared<memoryrepo::MemoryRepo<domain::Customer>>();
        std::shared_ptr<controller::Controller> ctrl = std::make_shared<controller::Controller>(repo1, repo2);

        ctrl->add("ABC", "type1", "2023/12/03", "Brasov, Romania", 12, domain::parked);
        ctrl->add("BSM", "BMW", "2022/04/23", "Florida", 1200, domain::in_use);
        ctrl->add("PLK", "Toyota", "2002/02/02", "Rome", 12, domain::out_of_use);
        ctrl->add("ASS", "Toyota", "2012/02/04", "Rome", 9323, domain::in_service);

        vector<shared_ptr<domain::Scooter>> scooters = ctrl->find_by_km(12);
        assert(scooters[0]->get_id() == "ABC");
        assert(scooters[1]->get_id() == "PLK");

        vector<shared_ptr<domain::Scooter>>scooters2 = ctrl->sort_by_age();
        assert(scooters2[0]->get_id() == "PLK");
        assert(scooters2[1]->get_id() == "ASS");
        assert(scooters2[2]->get_id() == "BSM");
        assert(scooters2[3]->get_id() == "ABC");

        vector<shared_ptr<domain::Scooter>> scooters3 = ctrl->find_by_location("Florida");
        assert(scooters3[0]->get_id() == "BSM");

        vector<shared_ptr<domain::Scooter>> scooters4 = ctrl->find_by_age("2023");
        assert(scooters4[0]->get_id() == "ABC");
        cout << "test controller passed\n";


    }

}
