#pragma once

#include "../Domain/Scooter.h"
#include "../Domain/Customer.h"
#include "../Repository/FileRepo.h"
#include "../Repository/Repo.h"

#include <memory>
#include <algorithm>
#include <string>

using namespace std;

namespace controller {

    class Controller {

    private:
        shared_ptr<Repo<domain::Scooter>> repo_scooter;
        shared_ptr<Repo<domain::Customer>> repo_customer;
        shared_ptr<domain::Customer> logged_in_customer;

    public:
        explicit Controller(shared_ptr<Repo<domain::Scooter>> scooterrepo,
                            shared_ptr<Repo<domain::Customer>> repo_customer);

        bool add(string id, string type, string first_use_date, string last_location, int km, domain::State state);

        bool remove(string id);

        bool update(string id, string type, string first_use_date, string last_location, int km, domain::State state);

        //crud for customerrepo

        bool set_logged_in_customer(string id);

        bool add_customer(string id, string name);

        bool remove_customer(string id);

        vector<shared_ptr<domain::Scooter>> get_reserved_scooters();

        vector<shared_ptr<domain::Customer>> get_all_customers();

        vector<shared_ptr<domain::Scooter>> find_by_location(string location);

        vector<shared_ptr<domain::Scooter>> find_by_km(int min_km, int max_km);

        vector<shared_ptr<domain::Scooter>> find_by_age(string substring);

        vector<shared_ptr<domain::Scooter>> sort_by_age();

        bool use_scooter(string id, int km, string new_location);

        bool reserve_scooter(string id);

        vector<shared_ptr<domain::Scooter>> get_all_scooters();
    };
}

