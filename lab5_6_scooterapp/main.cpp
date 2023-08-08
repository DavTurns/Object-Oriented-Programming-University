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

int main() {

    test::test_repo();
    test::test_controller();

    int option;
    cout << "1.Persistent\n"
            "2.Flüchtig\n";

    cin >> option;

    std::shared_ptr<Repo<domain::Scooter>> reposcooter;
    std::shared_ptr<Repo<domain::Customer>> customer_repo;

    if(option == 1){
        reposcooter = std::make_shared<ScooterFileRepo>("C://Users//Latitude//Desktop//lab5_II//scooters.csv");
        customer_repo = std::make_shared<CustomerFileRepo>("C://Users//Latitude//Desktop//lab5_II//customers.csv");
    }

    if(option == 2){
        reposcooter = std::make_shared<memoryrepo::MemoryRepo<domain::Scooter>>();
        customer_repo = std::make_shared<memoryrepo::MemoryRepo<domain::Customer>>();
    }

    //std::shared_ptr<memoryrepo::MemoryRepo<domain::Scooter>> repo1 = std::make_shared<memoryrepo::MemoryRepo<domain::Scooter>>();
    std::shared_ptr<controller::Controller> ctrl = std::make_shared<controller::Controller>(reposcooter, customer_repo);
    ui::UI u(ctrl);

    u.menu();
    return 0;
}
