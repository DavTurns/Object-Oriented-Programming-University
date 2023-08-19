#ifndef LAB5_II_CUSTOMERFILEREPO_H
#define LAB5_II_CUSTOMERFILEREPO_H

#include "FileRepo.h"
#include "../Domain/Customer.h"

#include <memory>
#include <algorithm>
#include <string>
#include <filesystem>
#include <fstream>
#include <map>


using namespace std;

class CustomerFileRepo : public FileRepo<domain::Customer> {
private:

public:
    CustomerFileRepo(string path);

    string list_to_string(vector<shared_ptr<domain::Customer>> &obj_list) override;

    vector<shared_ptr<domain::Customer>> to_obj_list(string) override;

    void create_new_file() override;
};

#endif //LAB5_II_CUSTOMERFILEREPO_H
