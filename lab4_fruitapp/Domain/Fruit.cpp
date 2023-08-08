//
// Created by Latitude on 24.04.2023.
//

#include "Fruit.h"
#include <string>

namespace domain {

    Fruit::Fruit(string name, string origin, string expirationdate, int price, int quantity) {
        this->name = name;
        this->origin = origin;
        this->expirationdate = expirationdate;
        this->price = price;
        this->quantity = quantity;
    }


//getters
    string Fruit::get_name() {
        return this->name;
    }

    string Fruit::get_origin() {
        return origin;
    }

    string Fruit::get_expirationdate() {
        return expirationdate;
    }

    int Fruit::get_price() {
        return price;
    }

    int Fruit::get_quantity() {
        return quantity;
    }

//setters
    void Fruit::set_price(int new_price) {
        this->price = new_price;
    }

    void Fruit::set_quantity(int new_quantity) {
        this->quantity = new_quantity;
    }
}
