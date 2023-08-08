//
// Created by Latitude on 24.05.2023.
//

#include "Customer.h"

namespace domain{

    Customer::Customer(string id, string name, vector<string> reserved_scooters) : id(id), name(name), reserved_scooters(reserved_scooters){}

    string Customer::get_id() {
        return id;
    }

    string Customer::get_name(){
        return name;
    }

    vector<string> Customer::get_scooterlist(){
        return reserved_scooters;
    }

    bool Customer::add_scooter(string &id){
        if(!has_scooter(id)){
            reserved_scooters.push_back(id);
        }
    }

    bool Customer::remove_scooter(string &id){
        for(int i = 0; i<reserved_scooters.size(); i++){
            if(id == reserved_scooters[i]) {
                reserved_scooters.erase(reserved_scooters.begin()+i);
                return true;
            }
        }
        return false;
    }

    bool Customer::has_scooter(string &id){
        for(int i = 0; i<reserved_scooters.size(); i++){
            if(id == reserved_scooters[i]){
                return true;
            }
        }
        return false;
    }
};