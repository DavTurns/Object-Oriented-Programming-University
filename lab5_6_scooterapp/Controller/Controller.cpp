
#include "Controller.h"
#include "../Repository/ScooterFileRepo.h"

#include <string>
#include <memory>

namespace controller {

    Controller::Controller(shared_ptr<Repo<domain::Scooter>> repo, shared_ptr<Repo<domain::Customer>> repo_customer) {
        this->repo = repo;
        this->repo_customer = repo_customer;
    }

    bool Controller::add(string id, string type, string first_use_date, string last_location, int km, domain::State state) {
        /*
        input: pointer of Scooter obj you want to add
        output: false, if ScooterObj with same id as scooter_ptr exists
                true, if added successfully
        */

        shared_ptr<domain::Scooter> scooter_ptr = make_shared<domain::Scooter>(id, type, first_use_date, last_location, km, state);
        return repo->add(scooter_ptr);
    }

    //CUSTOMERMETHODS___________________________________________

    bool Controller::add_customer(string id, string name) {
        vector<string> temp;
        shared_ptr<domain::Customer> customer = make_shared<domain::Customer>(id, name, temp);
        return repo_customer->add(customer);
    }

    bool Controller::remove_customer(string id) {
        return repo_customer->remove(id);
    }

    vector<shared_ptr<domain::Customer>> Controller::get_all_customers() {
        return repo_customer->find_all();
    }

    bool Controller::exists_in_customer_repo(string id) {
        vector<shared_ptr<domain::Customer>> customers = repo_customer->find_all();
        for(auto customer : customers){
            if(customer->get_id() == id){
                return true;
            }
        }
        return false;
    }

    void Controller::set_customerid(string id) {
        customerid = id;
    }
    //___________________________________________________________

    bool Controller::remove(string &id) {
        //output: true if scooter with id found and removed successfully,
        //        else false
        return repo->remove(id);
    }

    bool Controller::update(string id, string type, string first_use_date, string last_location, int km, domain::State state) {
        //output: true if scooter with same id exists
        //        false if scooter not updated successfully because scooter with same id as scooter_ptr doesnt exist

        shared_ptr<domain::Scooter> scooter_ptr = make_shared<domain::Scooter>(id, type, first_use_date, last_location, km, state);
        return repo->update(scooter_ptr);
    }

    bool Controller::change_state(string id, domain::State state) {
        vector<shared_ptr<domain::Scooter>> scooters = repo->find_all();
        for (auto it = scooters.begin(); it != scooters.end(); it++) {
            if ((*it)->get_id() == id) {
                (*it)->set_state(state);
                repo->update(*it);
                return true;
            }
        }
        return false;
    }

    bool Controller::use_scooter(string id, int km, string new_location) {
        vector<shared_ptr<domain::Scooter>> scooters = repo->find_all();
        auto it = find_if(scooters.begin(),scooters.end(),[&](shared_ptr<domain::Scooter> scooter){
            return scooter->get_id() == id;
        });
        if(it != scooters.end()){
            (*it)->set_state(domain::parked);
            (*it)->set_km((*it)->get_km()+km);
            (*it)->set_last_location(new_location);
            repo->update(*it);
            vector<shared_ptr<domain::Customer>> customerlist = repo_customer->find_all();
            for(auto customer : customerlist) {
                if (customer->get_id() == customerid) {
                    customer->remove_scooter(id);
                    repo_customer->update(customer);
                    change_state((*it)->get_id(), domain::parked);
                }
            }
            return true;
        } else {
            return false;
        }
    }

    vector<shared_ptr<domain::Scooter>> Controller::find_by_location(string location) {
        vector<shared_ptr<domain::Scooter>> scooters = repo->find_all();
        vector<shared_ptr<domain::Scooter>> filtered_scooters;
        for(int i = 0; i<scooters.size();i++){
            if (scooters[i]->get_last_location().find(location) != std::string::npos) {
                filtered_scooters.push_back(scooters[i]);
            }
        }
        return filtered_scooters;
    }

    vector<shared_ptr<domain::Scooter>> Controller::find_by_km(int km) {
        //returns vector with all the object that match a certain km count
        vector<shared_ptr<domain::Scooter>> scooters = repo->find_all();
        vector<shared_ptr<domain::Scooter>> filtered_scooters;
        for(int i = 0; i<scooters.size();i++){
            if (scooters[i]->get_km() == km) {
                filtered_scooters.push_back(scooters[i]);
            }
        }

        return filtered_scooters;
    }

    vector<shared_ptr<domain::Scooter>> Controller::find_by_age(string substring) {
        /*
        returns a vector of pointer to objects which contain the substring as parameter
         */

        vector<shared_ptr<domain::Scooter>> scooters = repo->find_all();
        vector<shared_ptr<domain::Scooter>> filtered_scooters;
        for(int i = 0; i<scooters.size();i++){
            if (scooters[i]->get_first_use_date().find(substring) != std::string::npos) {
                filtered_scooters.push_back(scooters[i]);
            }
        }
        return filtered_scooters;
    }

    vector<shared_ptr<domain::Scooter>> Controller::sort_by_age() {
        vector<shared_ptr<domain::Scooter>> scooters = repo->find_all();

        //helping function
        auto date_to_int = [](string date){
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

    void Controller::reserve_scooter(string id) {
        //changes the status of the selected scooter to reserved
        if(change_state(id, domain::State::reserved)){
            vector<shared_ptr<domain::Customer>> customerlist = repo_customer->find_all();
            for(auto customer : customerlist){
                if(customer->get_id() == customerid){
                    customer->add_scooter(id);
                    repo_customer->update(customer);
                    change_state(id, domain::reserved);

                }
            }
        }
    }

    vector<shared_ptr<domain::Scooter>> Controller::return_scooters(){
        return repo->find_all();;
    }

    vector<shared_ptr<domain::Scooter>> Controller::get_reserved_scooters() {
        vector<shared_ptr<domain::Customer>> customers = repo_customer->find_all();
        for(auto customer : customers){
            if(customer->get_id() == customerid){

                vector<string> reserved_scooters_ids = customer->get_scooterlist();

                vector<shared_ptr<domain::Scooter>> scooters = repo->find_all();

                vector<shared_ptr<domain::Scooter>> reserved_scooters;
                for(auto scooter_id : reserved_scooters_ids){
                    for(auto scooter : scooters){
                        if(scooter->get_id() == scooter_id){
                            reserved_scooters.push_back(scooter);
                        }
                    }
                }
                return reserved_scooters;
            }
        }
    }

}