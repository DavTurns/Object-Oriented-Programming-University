#pragma once

#include <iostream>
#include <string>
#include "../Controller/Controller.h"
#include <memory>

namespace ui {
    class UI {
    private:
        shared_ptr<controller::Controller> ctrl;

    public:
        UI(shared_ptr<controller::Controller> ctrl);

        void main_menu();

        void menu_customer();

        void menu_manager();

        void print_customer_menu();

        void print_manager_menu();

        void print_all_scooters();

        void show_scooters(vector<shared_ptr<domain::Scooter>>);

        void insert_scooter();

        void remove_scooter();

        void update_scooter();

        void get_by_last_location();

        void get_by_age();

        void get_by_km();

        void reserved_by_client();

        void used_by_client();

        void cout_ctrl();

        void sort_age();

        //customer CRUD

        void add_customer();

        void remove_customer();

        //void update_customer();

        void show_customers();

        void show_reserved_scooters();
    };
}


