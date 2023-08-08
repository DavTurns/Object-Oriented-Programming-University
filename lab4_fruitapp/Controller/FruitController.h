//
// Created by Latitude on 24.04.2023.
//

#ifndef LAB4_FRUITCONTROLLER_H
#define LAB4_FRUITCONTROLLER_H

#include <string>
#include <vector>

#include "../Domain/Fruit.h"
#include "../Repository/FruitRepo.h"

namespace controller {

    class FruitController {

    public:
        FruitController(repository::FruitRepo &);

        void add(string name, string origin, string expirationdate, int price, int quantity);
        //void delete(string name, string origin);
        //void find(type_info);

        void delete_fruit(string name, string origin);

        shared_ptr<vector<shared_ptr<domain::Fruit>>> find_with_substring(string);

        shared_ptr<vector<shared_ptr<domain::Fruit>>> filter_shortage(int max_quantity);

        shared_ptr<vector<shared_ptr<domain::Fruit>>> sorted_expiration_date();

    private:
        repository::FruitRepo &repo;

        int convert_date_to_int(string);
    };

}

#endif //LAB4_FRUITCONTROLLER_H
