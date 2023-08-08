//
// Created by Maria on 5/13/2023.
//

#pragma once

#include <iostream>

using namespace std;

namespace domain {
    enum State {
        reserved, parked, in_service, out_of_use, in_use
    };

    class Scooter {
    private:
        string id, type, first_use_date, last_location;
        int km;
        State state;

    public:
        Scooter(string id, string type, string first_use_date, string last_location, int km, State state);

        //getters
        string get_id();

        string get_type();

        string get_first_use_date();

        string get_last_location();

        int get_km();

        State get_state();

        //setters
        void set_last_location(string new_location);

        void set_km(int new_km);

        void set_state(State new_state);


    };
}



