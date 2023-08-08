//
// Created by Maria on 5/13/2023.
//

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

        void menu();

        void scooters();

        void show_scooters(vector<shared_ptr<domain::Scooter>>);

        void insert_scooter();

        void remove_scooter();

        void update_scooter();

        void get_by_last_location();

        void get_by_age();

        void get_by_km();

        void text();

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


