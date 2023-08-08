
#include "UI.h"
#include "../Controller/Controller.h"
#include <memory>

using namespace domain;
namespace ui {
    UI::UI(shared_ptr<controller::Controller> c) : ctrl(c) {

        ctrl->add("ABC", "type1", "2023/12/03", "Brasov Romania", 12, domain::parked);
        ctrl->add("BSM", "BMW", "2022/04/23", "Florida", 1200, domain::in_use);
        ctrl->add("ALO", "Mercedes", "2023/07/05", "Rome Italy", 340, domain::in_use);
        ctrl->add("SRI", "BMW", "2020/04/19", "Florida", 24423, domain::reserved);
        ctrl->add("PLK", "Toyota", "2002/02/02", "Rome", 23, domain::out_of_use);
        ctrl->add("ASS", "Toyota", "2012/02/04", "Rome", 9323, domain::in_service);
        ctrl->add("APP", "Toyota", "2023/04/12", "Rome", 26523, domain::reserved);
        ctrl->add("BAL", "Toyota", "2022/12/02", "Slovenia", 23123, domain::out_of_use);
        ctrl->add("CCC", "Porsche", "2023/03/02", "Corfu", 8323, domain::in_use);
        ctrl->add("KlA", "Lambo", "2021/10/09", "Rimini", 96, domain::parked);

        ctrl->add_customer("001","Max Mustermann");
        ctrl->add_customer("002","Elon Musk");
    }

    void UI::scooters() {
        for (const auto &element: ctrl->return_scooters()) {
            domain::State state = element->get_state();
            string state_string;
            if (state == 0) state_string = "reserved";
            if (state == 1) state_string = "parked";
            if (state == 2) state_string = "in service";
            if (state == 3) state_string = "out of use";
            if (state == 4) state_string = "in use";
            cout << "Scooter : " << element->get_id() << ", of type " << element->get_type() << ", first used on "
                 << element->get_first_use_date()
                 << " ,last seen in  " << element->get_last_location() << " with " << element->get_km()
                 << "km, in state: " << state_string << "\n";
        }
    }

    void UI::show_scooters(vector<shared_ptr<Scooter>> scooters) {
        for (const auto &element: scooters) {
            domain::State state = element->get_state();
            string state_string;
            if (state == 0) state_string = "reserved";
            if (state == 1) state_string = "parked";
            if (state == 2) state_string = "in service";
            if (state == 3) state_string = "out of use";
            if (state == 4) state_string = "in use";
            cout << "Scooter : " << element->get_id() << ", of type " << element->get_type() << ", first used on "
                 << element->get_first_use_date()
                 << " ,last seen in  " << element->get_last_location() << " with " << element->get_km()
                 << "km, in state: " << state_string << "\n";
        }
    }

    void UI::update_scooter() {
        scooters();
        string id, type, date, location;
        int km, option;
        domain::State state;
        cout << "Which scooter do you wish to update: \n";
        cin >> id;
        cout << "New type: \n";
        cin >> type;
        cout << "New date: \n";
        cin >> date;
        cout << "New location: \n";
        cin >> location;
        cout << "New km: \n";
        cin >> km;
        cout << "New state: \n";
        cin >> option;
        if (option == 1) {
            state = domain::State::reserved;
        } else if (option == 2) {
            state = domain::State::parked;
        } else if (option == 3) {
            state = domain::State::in_use;
        } else if (option == 4) {
            state = domain::State::out_of_use;
        } else {
            state = domain::State::in_service;
        }

        ctrl->update(id, type, date, location, km, state);
        scooters();
    }

    void UI::insert_scooter() {
        string id, type, first_use_date, last_location;
        int km, option;
        domain::State state;
        cout << "Enter id of scooter: ";
        cin >> id;
        cout << "Enter type of scooter: ";
        cin >> type;
        cout << "Enter first use date of scooter (Year/Month/Day): ";
        cin >> first_use_date;
        cout << "Enter last location of scooter: ";
        cin >> last_location;
        cout << "Enter scooter km count: ";
        cin >> km;
        cout << "Please choose a state: ";
        cout << "\n";
        cout << "1. reserved" << "\n";
        cout << "2. parked" << "\n";
        cout << "3. in use" << "\n";
        cout << "4. out of use" << "\n";
        cout << "5. in service \n";
        cin >> option;
        if (option == 1) {
            state = domain::State::reserved;
        } else if (option == 2) {
            state = domain::State::parked;
        } else if (option == 3) {
            state = domain::State::in_use;
        } else if (option == 4) {
            state = domain::State::out_of_use;
        } else {
            state = domain::State::in_service;
        }
        ctrl->add(id, type, first_use_date, last_location, km, state);
        scooters();
    }

    void UI::remove_scooter() {
        string id;
        cout << "These are the available scooters: \n";
        scooters();
        cout << "\n";
        cout << "Which scooter do you wish to remove?";
        cin >> id;
        ctrl->remove(id);
        cout << "These are the remaining scooters:\n ";
        scooters();
    }

    void UI::get_by_age() {
        string age;
        cout << "What's the age of the scooter?: ";
        cin >> age;
        vector<shared_ptr<Scooter>> element = ctrl->find_by_age(age);
        for (int i = 0; i < element.size(); i++) {
            State state = element[i]->get_state();
            string state_string;
            if (state == 0) state_string = "reserved";
            if (state == 1) state_string = "parked";
            if (state == 2) state_string = "in service";
            if (state == 3) state_string = "out of use";
            if (state == 4) state_string = "in use";
            cout << "Scooter : " << element[i]->get_id() << ", of type " << element[i]->get_type() << ", first used on "
                 << element[i]->get_first_use_date()
                 << " ,last seen in  " << element[i]->get_last_location() << " with " << element[i]->get_km()
                 << "km, in state: " << state_string;
        }
    }

    void UI::get_by_km() {
        int km;
        cout << "km count";
        cin >> km;
        vector<shared_ptr<domain::Scooter>> element = ctrl->find_by_km(km);
        for (int i = 0; i < element.size(); i++) {
            domain::State state = element[i]->get_state();
            string state_string;
            if (state == 0) state_string = "reserved";
            if (state == 1) state_string = "parked";
            if (state == 2) state_string = "in service";
            if (state == 3) state_string = "out of use";
            if (state == 4) state_string = "in use";
            cout << "Scooter : " << element[i]->get_id() << ", of type " << element[i]->get_type() << ", first used on "
                 << element[i]->get_first_use_date()
                 << " ,last seen in  " << element[i]->get_last_location() << " with " << element[i]->get_km()
                 << "km, in state: " << state_string;
        }
    }

    void UI::get_by_last_location() {
        string last_location;
        cout << "What's the last location of the scooter?: ";
        cin >> last_location;
        vector<shared_ptr<domain::Scooter>> element = ctrl->find_by_location(last_location);
        for (int i = 0; i < element.size(); i++) {
            domain::State state = element[i]->get_state();
            string state_string;
            if (state == 0) state_string = "reserved";
            if (state == 1) state_string = "parked";
            if (state == 2) state_string = "in service";
            if (state == 3) state_string = "out of use";
            if (state == 4) state_string = "in use";
            cout << "Scooter : " << element[i]->get_id() << ", of type " << element[i]->get_type() << ", first used on "
                 << element[i]->get_first_use_date()
                 << " ,last seen in  " << element[i]->get_last_location() << " with " << element[i]->get_km()
                 << "km, in state: " << state_string;
        }
    }


    void UI::text() {
        cout << "Please choose an action: ";
        cout << "\n";
        cout << "1. Insert a scooter" << "\n";
        cout << "2. Remove a scooter" << "\n";
        cout << "3. Update a scooter" << "\n";
        cout << "4. Find a scooter by its last location" << "\n";
        cout << "5. Find scooters by age \n";
        cout << "6. Find scooters by km \n";
        cout << "7. Sort scooters by age \n";
        cout << "8. Add customer \n";
        cout << "9. Delete customer \n";
        cout << "10. Show all customers \n";
        cout << "0. End actions, exit programm" << "\n";
    }

    void UI::reserved_by_client() {
        string id;
        cout << "These are the available scooters:\n";
        scooters();
        cout << "Select one to reserve by id: \n";
        cin >> id;
        ctrl->reserve_scooter(id);
        scooters();

    }

    void UI::used_by_client() {
        string id, last_location;
        int km;
        cout << "ID: \n";
        cin >> id;
        cout << "Last location: \n";
        cin >> last_location;
        cout << "Km: \n";
        cin >> km;
        ctrl->use_scooter(id, km, last_location);
        scooters();
    }

    void UI::sort_age() {
        vector<shared_ptr<domain::Scooter>> element = ctrl->sort_by_age();
        for (int i = 0; i < element.size(); i++) {
            domain::State state = element[i]->get_state();
            string state_string;
            if (state == 0) state_string = "reserved";
            if (state == 1) state_string = "parked";
            if (state == 2) state_string = "in service";
            if (state == 3) state_string = "out of use";
            if (state == 4) state_string = "in use";
            cout << "Scooter : " << element[i]->get_id() << ", of type " << element[i]->get_type() << ", first used on "
                 << element[i]->get_first_use_date()
                 << " ,last seen in  " << element[i]->get_last_location() << " with " << element[i]->get_km()
                 << "km, in state: " << state_string << "\n";
        }
    }

    void UI::add_customer() {
        string id, name;
        cout << "\nNew ID:";
        cin >> id;
        cout << "\nNew Name:";
        cin >> name;

        if (ctrl->add_customer(id, name)) cout << "User " << name << " was added successfully!";
        else cout << "Error - ID " << id << " is already taken!";
    }

    void UI::remove_customer() {
        string id;
        cout << "\nID you want to delete:";
        cin >> id;
        if (ctrl->remove_customer(id)) cout << "ID: " << id << " removed successfully!";
        else cout << "Error - Customer with ID" << id << " does not exist";
    }

    //void UI::update_customer()

    void UI::show_customers() {
        cout << "Here are all customers with their reserved scooters: \n\n\n";
        cout << "ID,name,reserved scooters\n";
        vector<shared_ptr<Customer>> customers = ctrl->get_all_customers();
        for (shared_ptr<Customer> customer: customers) {
            cout << customer->get_id() << "," << customer->get_name() << ",";

            for (auto scooter: customer->get_scooterlist()) {
                cout << scooter << " ";
            }
        }
    }

    void UI::show_reserved_scooters() {
        show_scooters(ctrl->get_reserved_scooters());
    }

    void UI::menu() {
        string user;
        cout << "Who are you? \n Press C for client or M for Manager";
        cin >> user;
        if (user == "M") {
            string password;
            cout << "Please input the password: ";
            cin >> password;
            if (password != "python") {
                cout << "Wrong password, try again!";
            } else {
                int action = 1;
                while (action != 0) {
                    text();
                    cin >> action;
                    if (action == 1) {
                        insert_scooter();
                    }
                    if (action == 2) {
                        remove_scooter();
                    }
                    if (action == 3) {
                        update_scooter();
                    }
                    if (action == 4) {
                        get_by_last_location();
                    }
                    if (action == 5) {
                        get_by_age();
                    }
                    if (action == 6) {
                        get_by_km();
                    }
                    if (action == 7) {
                        sort_age();
                    }
                    if (action == 8) {
                        add_customer();
                    }
                    if (action == 9) {
                        remove_customer();
                    }
                    if (action == 10) {
                        show_customers();
                    }
                    /*if (action == 11) {
                        update_customer();
                    }*/
                }
            }
        }
        if (user == "C") {
            string id;
            while (true) {
                cout << "Please enter customerid";
                cin >> id;
                if (!ctrl->exists_in_customer_repo(id)) {
                    cout << "Error - customer doesnt exist in database";
                    continue;
                }
                break;
            }

            ctrl->set_customerid(id);

            int action2 = 1;
            while (action2 != 0) {
                cout << "Please choose an action: ";
                cout << "\n";
                cout << "1. Find a scooter by its last location" << "\n";
                cout << "2. Find scooters by age \n";
                cout << "3. Find scooters by km \n";
                cout << "4. Reserve a scooter \n";
                cout << "5. Use a scooter \n";
                cout << "6. Show reserved Scooters \n";
                cout << "0. End actions, exit programm" << "\n";
                cin >> action2;
                if (action2 == 1) {
                    get_by_last_location();
                }
                if (action2 == 2) {
                    get_by_age();
                }
                if (action2 == 3) {
                    get_by_km();
                }
                if (action2 == 4) {
                    reserved_by_client();
                }
                if (action2 == 5) {
                    used_by_client();
                }
                if (action2 == 6) {
                    show_reserved_scooters();
                }
            }
        }
    }
}
