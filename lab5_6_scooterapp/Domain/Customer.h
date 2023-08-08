//
// Created by Latitude on 24.05.2023.
//

#ifndef LAB5_II_CUSTOMER_H
#define LAB5_II_CUSTOMER_H

#include <vector>
#include <string>

using namespace std;

namespace domain {

    class Customer {
    private:
        string id;
        string name;
        vector<string> reserved_scooters;
    public:

        Customer(string id, string name, vector<string> reserved_scooters);

        string get_id();

        string get_name();

        vector<string> get_scooterlist();

        bool add_scooter(string &id);

        bool remove_scooter(string &id);

        bool has_scooter(string &id);
    };
}


#endif //LAB5_II_CUSTOMER_H
