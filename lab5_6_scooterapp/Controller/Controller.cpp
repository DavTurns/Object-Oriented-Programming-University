#include "Controller.h"
#include "../Repository/ScooterFileRepo.h"

#include <string>
#include <memory>

namespace controller {

    Controller::Controller(shared_ptr<Repo<domain::Scooter>> repo, shared_ptr<Repo<domain::Customer>> repo_customer) {
        this->repo_scooter = repo;
        this->repo_customer = repo_customer;
    }

    bool Controller::add(string id, string type, string first_use_date, string last_location, int km, domain::State state) {
        /*
        input: pointer of Scooter obj you want to add
        output: false, if ScooterObj with same id as scooter_ptr exists
                true, if added successfully
        */

        shared_ptr<domain::Scooter> scooter_ptr = make_shared<domain::Scooter>(id, type, first_use_date, last_location,
                                                                               km, state);
        return repo_scooter->add(scooter_ptr);
    }

    //CUSTOMERMETHODS___________________________________________

    bool Controller::add_customer(string id, string name) {
        vector<string> temp;
        shared_ptr<domain::Customer> customer = make_shared<domain::Customer>(id, name, temp);
        return repo_customer->add(customer);
    }

    bool Controller::remove_customer(string id) {
        /*
         * returns true if customer was removed successfully else false
         * */
        vector<shared_ptr<domain::Customer>> customerlist = repo_customer->find_all();
        if (repo_customer->remove(id)) {

            //find customer
            for (auto customer: customerlist) {

                if (customer->get_id() == id) {

                    vector<string> reserved_scooter_ids = customer->get_reserved_scooters();
                    vector<shared_ptr<domain::Scooter>> scooter_list = repo_scooter->find_all();

                    //set all reserved scooters of this customer to parked
                    for (auto scooter_id: reserved_scooter_ids) {

                        for (auto scooter: scooter_list) {

                            if (scooter_id == scooter->get_id()) {
                                scooter->set_state(domain::State::parked);
                                repo_scooter->update(scooter);
                            }
                        }
                    }
                    return true;
                }
            }
        }
        return false;

    }

    vector<shared_ptr<domain::Customer>> Controller::get_all_customers() {
        return repo_customer->find_all();
    }

    bool Controller::set_logged_in_customer(string id) {
        /* returns true if the logged_in_customer was set successfully
         * else false
         */
        vector<shared_ptr<domain::Customer>> customers = repo_customer->find_all();

        for (auto customer: customers) {
            if (customer->get_id() == id) {
                logged_in_customer = customer;
                return true;
            }
        }
        return false;
    }
    //___________________________________________________________

    bool Controller::remove(string id) {
        //output: true if scooter with id found and removed successfully,
        //        else false

        if (repo_scooter->remove(id)) {
            vector<shared_ptr<domain::Customer>> customerlist = repo_customer->find_all();
            for (auto customer: customerlist) customer->remove_scooter(id);
            return true;
        }
        return false;
    }

    bool Controller::update(string id, string type, string first_use_date, string last_location, int km,
                            domain::State state) {
        //output: true if scooter with same id exists
        //        false if scooter not updated successfully because scooter with same id as scooter_ptr doesnt exist

        shared_ptr<domain::Scooter> scooter_ptr = make_shared<domain::Scooter>(id, type, first_use_date, last_location,
                                                                               km, state);
        return repo_scooter->update(scooter_ptr);
    }

    bool Controller::use_scooter(string id, int km, string new_location) {
        /*
         * returns true if id of scooter was found and if reserved that its reserved by current user
         * */

        vector<shared_ptr<domain::Scooter>> scooters = repo_scooter->find_all();
        auto it = find_if(scooters.begin(), scooters.end(), [&](shared_ptr<domain::Scooter> scooter) {
            return scooter->get_id() == id;
        });

        if (it != scooters.end()) {
            if ((*it)->get_state() == domain::reserved) {
                if (!logged_in_customer->has_scooter((*it)->get_id())) return false;
            }

            (*it)->set_state(domain::parked);
            (*it)->set_km((*it)->get_km() + km);
            (*it)->set_last_location(new_location);
            repo_scooter->update(*it);
            vector<shared_ptr<domain::Customer>> customerlist = repo_customer->find_all();

            logged_in_customer->remove_scooter(id);
            repo_customer->update(logged_in_customer);

            return true;
        } else return false;
    }

    vector<shared_ptr<domain::Scooter>> Controller::find_by_location(string location) {
        vector<shared_ptr<domain::Scooter>> scooters = repo_scooter->find_all();
        vector<shared_ptr<domain::Scooter>> filtered_scooters;
        for (int i = 0; i < scooters.size(); i++) {
            if (scooters[i]->get_last_location().find(location) != std::string::npos) {
                filtered_scooters.push_back(scooters[i]);
            }
        }
        return filtered_scooters;
    }

    vector<shared_ptr<domain::Scooter>> Controller::find_by_km(int min_km, int max_km) {
        //returns vector with all the object that match a certain km count
        vector<shared_ptr<domain::Scooter>> scooters = repo_scooter->find_all();
        vector<shared_ptr<domain::Scooter>> filtered_scooters;
        int km_scooter;

        for (int i = 0; i < scooters.size(); i++) {
            km_scooter = scooters[i]->get_km();
            if (km_scooter >= min_km and km_scooter <= max_km) {
                filtered_scooters.push_back(scooters[i]);
            }
        }
        return filtered_scooters;
    }

    vector<shared_ptr<domain::Scooter>> Controller::find_by_age(string substring) {
        /*
        returns a vector of pointer to objects which contain the substring as parameter
        */
        vector<shared_ptr<domain::Scooter>> scooters = repo_scooter->find_all();
        vector<shared_ptr<domain::Scooter>> filtered_scooters;
        for (int i = 0; i < scooters.size(); i++) {
            if (scooters[i]->get_first_use_date().find(substring) != std::string::npos) {
                filtered_scooters.push_back(scooters[i]);
            }
        }
        return filtered_scooters;
    }

    vector<shared_ptr<domain::Scooter>> Controller::sort_by_age() {
        vector<shared_ptr<domain::Scooter>> scooters = repo_scooter->find_all();

        //helping function
        auto date_to_int = [](string date) {
            // Find and remove all occurrences of "."
            size_t dotPos = date.find('/');
            while (dotPos != std::string::npos) {
                date.erase(dotPos, 1);
                dotPos = date.find('/', dotPos);
            }
            return date;
        };

        sort(scooters.begin(), scooters.end(),
             [&](const shared_ptr<domain::Scooter> &a, const shared_ptr<domain::Scooter> &b) {
                 return date_to_int(a->get_first_use_date()) < date_to_int(b->get_first_use_date());
             });
        return scooters;
    }

    bool Controller::reserve_scooter(string id) {
        //changes the status of the selected scooter to reserved
        // and adds it to the list of reserved print_all_scooters of the logged in customer

        vector<shared_ptr<domain::Scooter>> scooters = repo_scooter->find_all();

        auto it = find_if(scooters.begin(), scooters.end(), [&](shared_ptr<domain::Scooter> &scooter) {
            if (scooter->get_id() == id and
                scooter->get_state() == domain::State::parked)
                return true;
            else return false;
        });

        if (it == scooters.end()) return false;
        else {
            (*it)->set_state(domain::State::reserved);
            logged_in_customer->add_scooter(id);
            repo_customer->update(logged_in_customer);
            repo_scooter->update(*it);
            return true;
        }
    }

    vector<shared_ptr<domain::Scooter>> Controller::get_all_scooters() {
        return repo_scooter->find_all();
    }

    vector<shared_ptr<domain::Scooter>> Controller::get_reserved_scooters() {

        vector<shared_ptr<domain::Customer>> customers = repo_customer->find_all();
        vector<shared_ptr<domain::Scooter>> scooters = repo_scooter->find_all();

        vector<string> reserved_scooters_ids = logged_in_customer->get_reserved_scooters();

        vector<shared_ptr<domain::Scooter>> reserved_scooters;
        for (auto scooter_id: reserved_scooters_ids) {
            for (auto scooter: scooters) {
                if (scooter->get_id() == scooter_id) {
                    reserved_scooters.push_back(scooter);
                    break;
                }
            }
        }
        return reserved_scooters;
    }
}