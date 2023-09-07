#include <vector>

#include "FruitRepo.h"
#include <algorithm>
#include <memory>

namespace repository {

    void FruitRepo::add(shared_ptr<domain::Fruit> fruitptr) {
        string name = fruitptr->get_name();
        string origin = fruitptr->get_origin();
        auto it = find_if(fruitlist.begin(), fruitlist.end(),
                          [name, origin](shared_ptr<domain::Fruit> fruitptr_fromlist) {
                              return fruitptr_fromlist->get_name() == name &&
                                     fruitptr_fromlist->get_origin() == origin;
                          });
        if (it == fruitlist.end()) {
            fruitlist.push_back(fruitptr);
        } else {
            int new_quantity = (*it)->get_quantity() + fruitptr->get_quantity();
            (*it)->set_quantity(new_quantity);
        }
    }

    void FruitRepo::delete_fruit(domain::Fruit &fruit) {

        auto it = find_if(fruitlist.begin(), fruitlist.end(), [&](shared_ptr<domain::Fruit> fruitptr) {
            return fruitptr->get_name() == fruit.get_name() &&
                   fruitptr->get_origin() == fruit.get_origin();
        });
        if (it != fruitlist.end()) {
            fruitlist.erase(it);
        }
    }

    int FruitRepo::get_size() {
        return fruitlist.size();
    }

    shared_ptr<vector<shared_ptr<domain::Fruit>>>

    FruitRepo::get_all() {
        shared_ptr<vector<shared_ptr<domain::Fruit>>> ptr = make_shared<vector<shared_ptr<
                domain::Fruit>>>(fruitlist);
        return ptr;
    }

}