//
// Created by Latitude on 24.05.2023.
//

#include "CustomerFileRepo.h"
#include <sstream>
CustomerFileRepo::CustomerFileRepo(string path) : FileRepo<domain::Customer>(path){};

string CustomerFileRepo::list_to_string(vector<shared_ptr<domain::Customer>> &obj_list){
    string content = "id,name,reserved_scooters\n";
    string obj_as_string;
    vector<string> reserved_scooters;

    for (int i = 0; i < obj_list.size(); i++) {
        obj_as_string = obj_list[i]->get_id() + ","
                        + obj_list[i]->get_name() + ",";
        reserved_scooters = obj_list[i]->get_scooterlist();
        for(string scooter: reserved_scooters){
            obj_as_string += scooter + ";";
        }
        if(obj_as_string.back() == ';'){
            obj_as_string.erase(obj_as_string.length()-1);
        }
        obj_as_string+="\n";
        content += obj_as_string;
    }
    content.erase(content.size() - 1);
    return content;
}

vector<shared_ptr<domain::Customer>> CustomerFileRepo::to_obj_list(string input){
    vector<shared_ptr<domain::Customer>> obj_list;

    // Process the CSV data line by line
    istringstream iss(input);
    string line;
    getline(iss, line); // this is the first line header
    while (getline(iss, line)) {
        // Split the line into individual values using a delimiter (e.g., comma)
        istringstream lineStream(line);
        string id, name, scooter_id;

        string reserved_scooters_as_string;
        vector<string> reserved_scooters;

        getline(lineStream, id, ',');
        getline(lineStream, name, ',');
        getline(lineStream, reserved_scooters_as_string, ',');

        istringstream scooterlistStream(reserved_scooters_as_string);

        while(getline(scooterlistStream, scooter_id, ';')){
            reserved_scooters.push_back(scooter_id);
        }
        // Create a new customer object and add it to the vector
        shared_ptr<domain::Customer> customer = make_shared<domain::Customer>(id, name, reserved_scooters);
        obj_list.push_back(customer);
    }
    return obj_list;
}