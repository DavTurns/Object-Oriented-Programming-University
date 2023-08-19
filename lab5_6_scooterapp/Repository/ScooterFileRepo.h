#ifndef LAB5_II_SCOOTERFILEREPO_H
#define LAB5_II_SCOOTERFILEREPO_H

#include "FileRepo.h"
#include "../Domain/Scooter.h"

#include <memory>
#include <algorithm>
#include <string>
#include <filesystem>
#include <fstream>
#include <map>

using namespace std;

class ScooterFileRepo : public FileRepo<domain::Scooter> {
public:
    ScooterFileRepo(string path);

    string list_to_string(vector<shared_ptr<domain::Scooter>> &obj_list) override;

    vector<shared_ptr<domain::Scooter>> to_obj_list(string) override;

    void create_new_file() override;
};

#endif //LAB5_II_SCOOTERFILEREPO_H
