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

        vector<string> get_reserved_scooters();

        bool add_scooter(string id);

        bool remove_scooter(string id);

        bool has_scooter(string id);
    };
}


#endif //LAB5_II_CUSTOMER_H
