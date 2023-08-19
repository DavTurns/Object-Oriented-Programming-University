#include "Scooter.h"

using namespace std;

#include <exception>

namespace domain {
    Scooter::Scooter(string id, string type, string first_use_date, string last_location, int km, State state) {
        if (id.size() != 3) {
            throw exception();
        }
        this->id = id;
        this->type = type;
        this->first_use_date = first_use_date;
        this->last_location = last_location;
        this->km = km;
        this->state = state;
    }

    //getters
    string Scooter::get_id() { return id; }

    string Scooter::get_first_use_date() { return first_use_date; }

    int Scooter::get_km() { return km; }

    State Scooter::get_state() { return state; }

    string Scooter::get_type() { return type; }

    string Scooter::get_last_location() { return last_location; }

    //setters
    void Scooter::set_km(int new_km) { km = new_km; }

    void Scooter::set_last_location(string new_location) { last_location = new_location; }

    void Scooter::set_state(State new_state) { state = new_state; }


}