#include "UI.h"
#include <memory>

using namespace domain;

namespace ui {

    UI::UI(shared_ptr<controller::Controller> c) : ctrl(c) {

        //adding sampledata in case that user runs program in non-persistent mode
        ctrl->add("ABC", "type1", "2023/12/03", "Brasov Romania", 12, domain::parked);
        ctrl->add("BSM", "BMW", "2022/04/23", "Florida", 1200, domain::in_use);
        ctrl->add("ALO", "Mercedes", "2023/07/05", "Rome Italy", 340, domain::in_use);
        ctrl->add("SRI", "BMW", "2020/04/19", "Florida", 24423, domain::parked);
        ctrl->add("PLK", "Toyota", "2002/02/02", "Rome", 23, domain::out_of_use);
        ctrl->add("ASS", "Toyota", "2012/02/04", "Rome", 9323, domain::in_service);
        ctrl->add("APP", "Toyota", "2023/04/12", "Rome", 26523, domain::parked);
        ctrl->add("BAL", "Toyota", "2022/12/02", "Slovenia", 23123, domain::out_of_use);
        ctrl->add("CCC", "Porsche", "2023/03/02", "Corfu", 8323, domain::in_use);
        ctrl->add("KlA", "Lambo", "2021/10/09", "Rimini", 96, domain::parked);

        ctrl->add_customer("001", "Max Mustermann");
        ctrl->add_customer("002", "Elon Musk");
    }

    void UI::main_menu() {
        string user;
        cout << "Who are you? \n Press C for client or M for Manager";
        cin >> user;
        if (user == "M") {
            menu_manager();
        }
        if (user == "C") {
            menu_customer();
        }
    }

    void UI::menu_customer() {
        string id;
        int action2 = 1;

        enter_customerid:
        cout << "Please enter customerid: ";
        cin >> id;
        if (!ctrl->set_logged_in_customer(id)) {
            cout << "Error - customer doesnt exist in database\n";
            goto enter_customerid;
        }

        while (action2 != 0) {
            system("pause");

            print_customer_menu();
            cin >> action2;

            if (action2 == 1) get_by_last_location();

            if (action2 == 2) get_by_age();

            if (action2 == 3) get_by_km();

            if (action2 == 4) reserved_by_client();

            if (action2 == 5) used_by_client();

            if (action2 == 6) show_reserved_scooters();
        }
    }

    void UI::menu_manager() {
        string password;

        enter_password:
        cout << "Please enter the password: ";
        cin >> password;
        if (password != "admin") {
            cout << "Wrong password, try again!\n";
            goto enter_password;
        } else {
            int action = 1;
            while (action != 0) {
                system("pause");

                print_manager_menu();
                cin >> action;

                if (action == 1) insert_scooter();

                if (action == 2) remove_scooter();

                if (action == 3) update_scooter();

                if (action == 4) get_by_last_location();

                if (action == 5) get_by_age();

                if (action == 6) get_by_km();

                if (action == 7) sort_age();

                if (action == 8) add_customer();

                if (action == 9) remove_customer();

                if (action == 10) show_customers();

                //if (action == 11) update_customer();
            }
        }
    }

    void UI::print_manager_menu() {
        cout << "Please choose an action:\n"
                "1. Insert a scooter\n"
                "2. Remove a scooter\n"
                "3. Update a scooter\n"
                "4. Find a scooter by its last location\n"
                "5. Find scooters by age\n"
                "6. Find scooters by km\n"
                "7. Sort scooters by age\n"
                "8. Add customer\n"
                "9. Delete customer\n"
                "10. Show all customers\n"
                "0. End actions, exit programm\n";
    }

    void UI::print_customer_menu() {
        cout << "Please choose an action:\n"
                "1. Find a scooter by its last location\n"
                "2. Find print_all_scooters by age\n"
                "3. Find print_all_scooters by km\n"
                "4. Reserve a scooter\n"
                "5. Use a scooter\n"
                "6. Show reserved Scooters\n"
                "0. End actions, exit programm\n";
    }

    void UI::print_all_scooters() {
        show_scooters(ctrl->get_all_scooters());
    }

    void UI::show_scooters(vector<shared_ptr<Scooter>> scooters) {
        string state_string;
        domain::State state;

        for (const auto &element: scooters) {
            state = element->get_state();
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
        string input, id, type, date, location;
        int km, option;
        domain::State state;

        print_all_scooters();
        selectid:
        cout << "Which scooter do you wish to update: \n";
        cin >> id;

        if (id.length() != 3) {
            cout << "Error - ID has to have length of 3 chars, please try again\n";
            goto selectid;
        }

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
        print_all_scooters();
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

        cout << "Please choose a state: \n";
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
        print_all_scooters();
    }

    void UI::remove_scooter() {
        string id;

        cout << "These are the available print_all_scooters: \n\n";
        print_all_scooters();
        cout << "Which scooter do you wish to remove?";
        cin >> id;

        ctrl->remove(id);
        cout << "These are the remaining print_all_scooters:\n ";
        print_all_scooters();
    }

    void UI::get_by_age() {
        string age;

        cout << "Type in preferred year, month or day: ";
        cin >> age;

        vector<shared_ptr<Scooter>> scooterlist = ctrl->find_by_age(age);
        show_scooters(scooterlist);
    }

    void UI::get_by_km() {
        int min_km, max_km;

        cout << "Type in following: min km, max km\n"
                "Min km:";
        cin >> min_km;
        cout << "Max km: ";
        cin >> max_km;

        vector<shared_ptr<domain::Scooter>> scooterlist = ctrl->find_by_km(min_km, max_km);
        show_scooters(scooterlist);

    }

    void UI::get_by_last_location() {
        string last_location;

        cout << "What's the last location of the scooter?"
                "(Please type the complete correct location, casesensitive): ";
        cin >> last_location;

        vector<shared_ptr<domain::Scooter>> scooterlist = ctrl->find_by_location(last_location);
        show_scooters(scooterlist);
    }

    void UI::reserved_by_client() {
        string id;

        cout << "These are the available scooters:\n";
        print_all_scooters();
        cout << "Select one to reserve by id: \n";
        cin >> id;

        if (ctrl->reserve_scooter(id)) cout << id << " reserved successfully\n\n";
        else cout << "No scooter available with entered id.\n\n";
    }

    void UI::used_by_client() {
        string id, last_location;
        int km;

        show_reserved_scooters();

        cout << "ScooterID: \n";
        cin >> id;

        cout << "New location: \n";
        cin >> last_location;

        cout << "Km traveled: \n";
        cin >> km;
        ctrl->use_scooter(id, km, last_location);
        print_all_scooters();
    }

    void UI::sort_age() {
        show_scooters(ctrl->sort_by_age());
    }

    void UI::add_customer() {
        string id, name;
        cout << "\nNew ID:";
        cin >> id;
        cout << "\nNew Name:";
        cin >> name;

        if (ctrl->add_customer(id, name)) cout << "User " << name << " was added successfully!\n";
        else cout << "Error - ID " << id << " is already taken!\n";

    }

    void UI::remove_customer() {
        string id;
        cout << "\nID you want to delete:";
        cin >> id;
        if (ctrl->remove_customer(id)) cout << "ID: " << id << " removed successfully!\n";
        else cout << "Error - Customer with ID" << id << " does not exist\n";
    }

    void UI::show_customers() {
        cout << "Here are all customers with their reserved scooter IDs:\n";
        cout << "ID,name,reserved scooters";

        vector<shared_ptr<Customer>> customers = ctrl->get_all_customers();
        for (shared_ptr<Customer> customer: customers) {
            cout << "\n" << customer->get_id() << "," << customer->get_name() << ",";

            for (auto scooter: customer->get_reserved_scooters()) {
                cout << scooter << " ";
            }
        }
        cout << "\n\n\n";
    }

    void UI::show_reserved_scooters() {
        cout << "Reserved scooters:\n";
        show_scooters(ctrl->get_reserved_scooters());
    }
}
