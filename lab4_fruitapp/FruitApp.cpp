//
// Created by Latitude on 24.04.2023.
//
#include "Controller/FruitController.h"
#include "Repository/FruitRepo.h"
#include "UI/FruitUI.h"
#include "Tests/tests.h"


int main() {

    //run tests
    test_controller_add_fruit();
    test_controller_delete_fruit();
    test_repository_get_all();

    //init and run the app
    repository::FruitRepo repo;
    controller::FruitController controller(repo);
    ui::FruitUI ui(controller);
    ui.menu();

    return 0;
}
