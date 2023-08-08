//
// Created by Latitude on 24.04.2023.
//



#ifndef LAB4_FRUITUI_H
#define LAB4_FRUITUI_H

#include "../Controller/FruitController.h"

namespace ui {

    class FruitUI {
    private:
        controller::FruitController &ctrl;

        void option_delete();

        void option_add();

        void option_search();

        void option_show_shortage();

        void option_show_sorted_expirationdate();

        void print_fruits(shared_ptr<vector<shared_ptr<domain::Fruit>>> fruitlist);

    public:
        void menu();

        FruitUI(controller::FruitController &);
    };
}


#endif //LAB4_FRUITUI_H
