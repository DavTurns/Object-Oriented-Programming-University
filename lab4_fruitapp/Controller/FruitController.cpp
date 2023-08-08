//
// Created by Latitude on 24.04.2023.
//

#include <memory>
#include <vector>
#include <algorithm>

#include "FruitController.h"
#include "../Repository/FruitRepo.h"

using namespace std;

namespace controller {

    FruitController::FruitController(repository::FruitRepo &repo) : repo(repo) {}

    void FruitController::add(string name, string origin, string expirationdate, int price, int quantity) {
        /*1.Wir suchen in fruitlist nach einem objekt, der diesselben Eigenschaften hat wie unser neues Objekt
         *  Wenn existiert,wird einfach die Anzahl erhöht
         *  Wenn nicht, wird neues Objekt erstellt und sharepointer hinzugefügt
         * */

        shared_ptr<domain::Fruit> newfruitptr = make_shared<domain::Fruit>(name, origin, expirationdate, price,
                                                                           quantity);
        repo.add(newfruitptr);

    }

    void FruitController::delete_fruit(string name, string origin) {
        // if an object with the same name AND origin as the parameters, then this is going to be deleted
        domain::Fruit fruit = domain::Fruit(name, origin, "", -1, -1);
        repo.delete_fruit(fruit);

    }

    shared_ptr<vector<shared_ptr<domain::Fruit>>> FruitController::find_with_substring(string substr) {

        shared_ptr<vector<shared_ptr<domain::Fruit>>> fruitlist = repo.get_all();
        shared_ptr<vector<shared_ptr<domain::Fruit>>> fruitlist_filtered = make_shared<vector<shared_ptr<domain::Fruit>>>();
        for (int i = 0; i < fruitlist->size(); i++) {
            //wenn substring nicht in name/domain dann lösche object
            if ((*fruitlist)[i]->get_name().find(substr) != string::npos ||
                (*fruitlist)[i]->get_origin().find(substr) != string::npos) {
                fruitlist_filtered->push_back((*fruitlist)[i]);
            }
        }
        sort((*fruitlist_filtered).begin(), (*fruitlist_filtered).end(),
             [](shared_ptr<domain::Fruit> f1, shared_ptr<domain::Fruit> f2) {
                 return f1->get_name() < f2->get_name();
             });
        return fruitlist_filtered;
    }

    shared_ptr<vector<shared_ptr<domain::Fruit>>> FruitController::filter_shortage(int max_quantity) {

        shared_ptr<vector<shared_ptr<domain::Fruit>>> fruitlist = repo.get_all();
        shared_ptr<vector<shared_ptr<domain::Fruit>>> fruitlist_filtered = make_shared<vector<shared_ptr<domain::Fruit>>>();
        for (int i = 0; i < fruitlist->size(); i++) {

            //wenn substring nicht in name/domain dann lösche object
            if ((*fruitlist)[i]->get_quantity() <= max_quantity) {
                fruitlist_filtered->push_back((*fruitlist)[i]);
            }
        }
        return fruitlist_filtered;
    }

    shared_ptr<vector<shared_ptr<domain::Fruit>>> FruitController::sorted_expiration_date() {
        shared_ptr<vector<shared_ptr<domain::Fruit>>> fruitlist = repo.get_all();
        sort(fruitlist->begin(), fruitlist->end(), [&](shared_ptr<domain::Fruit> f1, shared_ptr<domain::Fruit> f2) {
            return convert_date_to_int(f1->get_expirationdate()) < convert_date_to_int(f2->get_expirationdate());
        });
        return fruitlist;
    }

    int FruitController::convert_date_to_int(string date) {
        date.erase(remove(date.begin(), date.end(), '/'), date.end());
        return stoi(date);
    }
}