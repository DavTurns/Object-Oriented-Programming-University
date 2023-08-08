//
// Created by Maria on 5/13/2023.
//

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
        shared_ptr<Repo<domain::Scooter>> repo;
        shared_ptr<Repo<domain::Customer>> repo_customer;

        string customerid;
    public:
        explicit Controller(shared_ptr<Repo<domain::Scooter>> scooterrepo, shared_ptr<Repo<domain::Customer>> repo_customer);

        bool add(string id, string type, string first_use_date, string last_location, int km, domain::State state);

        bool remove(string &id);

        bool update(string id, string type, string first_use_date, string last_location, int km, domain::State state);

        //crud for customerrepo

        void set_customerid(string id);

        bool add_customer(string id,string name);

        bool remove_customer(string id);

        bool update_customer(string id, string name);

        vector<shared_ptr<domain::Scooter>> get_reserved_scooters();

        vector<shared_ptr<domain::Customer>> get_all_customers();

        bool exists_in_customer_repo(string id);

        vector<shared_ptr<domain::Scooter>> find_by_location(string location);

        vector<shared_ptr<domain::Scooter>> find_by_km(int km);

        vector<shared_ptr<domain::Scooter>> find_by_age(string substring);

        vector<shared_ptr<domain::Scooter>> sort_by_age();

        bool change_state(string id, domain::State state);

        bool use_scooter(string id, int km, string new_location);

        void reserve_scooter(string id);

        vector<shared_ptr<domain::Scooter>> return_scooters();

    };
}

