//
// Created by Latitude on 24.04.2023.
//

#ifndef LAB4_FRUITREPO_H
#define LAB4_FRUITREPO_H

#include <vector>
#include <memory>

#include "../Domain/Fruit.h"

namespace repository {

    class FruitRepo {
    public:
        int get_size();

        void add(shared_ptr <domain::Fruit>);

        void delete_fruit(domain::Fruit &);

        shared_ptr <vector<shared_ptr < domain::Fruit>>>

        get_all();

    private:
        vector <shared_ptr<domain::Fruit>> fruitlist;
    };

}
#endif //LAB4_FRUITREPO_H
