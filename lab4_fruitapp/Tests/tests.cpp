//
// Created by Latitude on 03.05.2023.
//

#include "../Controller/FruitController.h"
#include "../Repository/FruitRepo.h"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

void test_controller_add_fruit() {

    repository::FruitRepo repo;
    controller::FruitController ctrl(repo);
    ctrl.add("Birne", "Russland", "11.11.2022", 12, 2);
    shared_ptr < vector < shared_ptr < domain::Fruit>>> fruitlist = repo.get_all();

    assert(repo.get_size() == 1);
    assert((*fruitlist)[0]->get_name() == "Birne" && (*fruitlist)[0]->get_origin() == "Russland");

    //by adding a fruit with same proprieties we increase the quantity
    ctrl.add("Birne", "Russland", "11.11.2022", 12, 1);
    fruitlist = repo.get_all();

    assert(repo.get_size() == 1);
    assert((*fruitlist)[0]->get_quantity() == 3);

    ctrl.add("Apfel", "Russland", "11.11.2022", 12, 2);
    fruitlist = repo.get_all();

    assert(repo.get_size() == 2);
    assert((*fruitlist)[1]->get_name() == "Apfel" && (*fruitlist)[1]->get_origin() == "Russland");

    cout << "test_controller_add_fruit PASSED\n";
}

void test_controller_delete_fruit() {

    //!!!It is assumed, that the add function is working properly!!!

    repository::FruitRepo repo;
    controller::FruitController ctrl(repo);

    ctrl.add("Birne", "Russland", "11.11.2022", 12, 2);
    ctrl.add("Apfel", "Russland", "11.11.2022", 12, 2);
    ctrl.add("Zwiebeln", "Russland", "11.11.2022", 12, 2);
    assert(repo.get_size() == 3);

    //deleting existing fruit
    ctrl.delete_fruit("Birne", "Russland");
    assert(repo.get_size() == 2);

    //deleting non existing fruits
    ctrl.delete_fruit("Banane", "Russland");
    assert(repo.get_size() == 2);
    ctrl.delete_fruit("Apfel", "England");
    assert(repo.get_size() == 2);

    cout << "test_controller_delete_fruit PASSED\n";
}

void test_get_all() {
    //!!!It is assumed, that the add function is working properly!!!

    repository::FruitRepo repo;
    controller::FruitController ctrl(repo);

    ctrl.add("Birne", "Russland", "11.11.2022", 12, 2);
    ctrl.add("Apfel", "Russland", "11.11.2022", 12, 2);
    ctrl.add("Zwiebeln", "Russland", "11.11.2022", 12, 2);
    assert(repo.get_size() == 3);

    shared_ptr < vector < shared_ptr < domain::Fruit>>> new_fruitlist = repo.get_all();
    assert(new_fruitlist->size() == 3);
    new_fruitlist->erase(new_fruitlist->begin() + 1);
    assert(new_fruitlist->size() == 2);
    assert(new_fruitlist->size() == 3);


}

void test_repository_get_all() {

    //!!!It is assumed, that the add function is working properly!!!

    repository::FruitRepo repo;
    controller::FruitController ctrl(repo);

    ctrl.add("Birne", "Russland", "11.11.2022", 12, 2);
    ctrl.add("Apfel", "Russland", "11.11.2022", 33, 2);
    ctrl.add("Zwiebeln", "Italy", "11.11.2022", 12, 2);
    assert(repo.get_size() == 3);

    shared_ptr < vector < shared_ptr < domain::Fruit>>> fruitlistptr = repo.get_all();
    assert((*fruitlistptr)[0]->get_name() == "Birne" && (*fruitlistptr)[0]->get_origin() == "Russland" &&
           (*fruitlistptr)[0]->get_expirationdate() == "11.11.2022" && (*fruitlistptr)[0]->get_price() == 12);
    assert((*fruitlistptr)[1]->get_name() == "Apfel" && (*fruitlistptr)[1]->get_origin() == "Russland" &&
           (*fruitlistptr)[1]->get_price() == 33);
    assert((*fruitlistptr)[2]->get_name() == "Zwiebeln" && (*fruitlistptr)[2]->get_origin() == "Italy" &&
           (*fruitlistptr)[2]->get_price() == 12);

    cout << "test_repository_get_all PASSED\n";
}