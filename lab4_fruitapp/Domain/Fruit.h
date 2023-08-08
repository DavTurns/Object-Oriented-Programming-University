//
// Created by Latitude on 24.04.2023.
//

#ifndef LAB4_FRUIT_H
#define LAB4_FRUIT_H

#include <string>

using namespace std;

namespace domain {

    class Fruit {
    private:

        string name;
        string origin;
        string expirationdate;

        int price;
        int quantity;

    public:

        //getters
        string get_name();

        string get_origin();

        string get_expirationdate();

        int get_price();

        int get_quantity();

        //setters
        void set_price(int);

        Fruit(string name, string origin, string expirationdate, int price, int quantity);

        void set_quantity(int new_quantity);
    };
}

#endif //LAB4_FRUIT_H
