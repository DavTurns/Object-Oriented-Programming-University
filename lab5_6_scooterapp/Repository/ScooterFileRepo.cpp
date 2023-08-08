//
// Created by Latitude on 24.05.2023.
//

#include "ScooterFileRepo.h"

#include <memory>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

ScooterFileRepo::ScooterFileRepo(string path) : FileRepo<domain::Scooter>(path) {}

string ScooterFileRepo::list_to_string(vector<shared_ptr<domain::Scooter>> &obj_list) {
    string content = "id,type,first_use_date,last_location,km,state\n";
    string obj_as_string;
    int km;

    for (int i = 0; i < obj_list.size(); i++) {
        km = obj_list[i]->get_km();
        obj_as_string = obj_list[i]->get_id() + ","
                        + obj_list[i]->get_type() + ","
                        + obj_list[i]->get_first_use_date() + ","
                        + obj_list[i]->get_last_location() + ","
                        + to_string(km) + ","
                        + stateMap[obj_list[i]->get_state()] + "\n";
        content += obj_as_string;
    }
    content.erase(content.size() - 1);
    return content;
}

vector<shared_ptr<domain::Scooter>> ScooterFileRepo::to_obj_list(string input) {
    vector<shared_ptr<domain::Scooter>> obj_list;

    // Process the CSV data line by line
    istringstream iss(input);
    string line;
    getline(iss, line); // this is the first line header
    while (getline(iss, line)) {
        // Split the line into individual values using a delimiter (e.g., comma)
        istringstream lineStream(line);
        string id, type, first_use_date, last_location, kmStr, stateStr;
        getline(lineStream, id, ',');
        getline(lineStream, type, ',');
        getline(lineStream, first_use_date, ',');
        getline(lineStream, last_location, ',');
        getline(lineStream, kmStr, ',');
        getline(lineStream, stateStr, ',');

        // Convert the string values to the appropriate types
        int km = stoi(kmStr);
        domain::State state;

        // Iterate over the map to find the key for the target value
        for (const auto &pair: stateMap) {
            if (pair.second == stateStr) {
                state = pair.first;
                break;  // Exit the loop if the target value is found
            }
        }
        // Create a new Scooter object and add it to the vector
        shared_ptr<domain::Scooter> scooter = make_shared<domain::Scooter>(id, type, first_use_date, last_location, km, state);
        obj_list.push_back(scooter);
    }
    return obj_list;
}

