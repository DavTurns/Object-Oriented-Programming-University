#include <iostream>

#include "./Tests/tests.h"
#include "UI/UI.h"

#include "Repository/MemoryRepo.h"
#include "Repository/Repo.h"
#include "Repository/ScooterFileRepo.h"
#include "Repository/CustomerFileRepo.h"

#include "Domain/Scooter.h"
#include "Controller/Controller.h"
#include <memory>
#include <string>

//change it to your preferences
//if files don't exist, they will be created and the sample data will be added automatically
const string PATH_CUSTOMER_REPO = "./customers.csv";
const string PATH_SCOOTER_REPO = "./scooters.csv";

int main() {
    test::test_repo();
    test::test_controller();

    string input;
    int option;

    std::cout << "  ____                  _                             \n"
                 " / ___|  ___ ___   ___ | |_ ___ _ __ __ _ _ __  _ __  \n"
                 " \\___ \\ / __/ _ \\ / _ \\| __/ _ \\ '__/ _` | '_ \\| '_ \\ \n"
                 "  ___) | (_| (_) | (_) | ||  __/ | | (_| | |_) | |_) |\n"
                 " |____/ \\___\\___/ \\___/ \\__\\___|_|  \\__,_| .__/| .__/ \n"
                 "                                         |_|   |_|    \n";

    while (true) {
        cout << "\nSelect mode:\n\n"
                "1.Persistent\n"
                "2.Non-persistent\n";
        cin >> input;

        try {
            option = stoi(input);
            if (option != 1 and option != 2) throw exception();
        } catch (const exception &e) {
            cout << "false input, try again\n";
            continue;
        }
        break;
    }

    std::shared_ptr<Repo<domain::Scooter>> reposcooter;
    std::shared_ptr<Repo<domain::Customer>> customer_repo;

    if (option == 1) {
        reposcooter = std::make_shared<ScooterFileRepo>(PATH_SCOOTER_REPO);
        customer_repo = std::make_shared<CustomerFileRepo>(PATH_CUSTOMER_REPO);
    }

    if (option == 2) {
        reposcooter = std::make_shared<memoryrepo::MemoryRepo<domain::Scooter>>();
        customer_repo = std::make_shared<memoryrepo::MemoryRepo<domain::Customer>>();
    }

    std::shared_ptr<controller::Controller> ctrl = std::make_shared<controller::Controller>(reposcooter, customer_repo);
    ui::UI u(ctrl);
    u.main_menu();
    return 0;
}
