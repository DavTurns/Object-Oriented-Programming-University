#ifndef LAB5_II_FILEREPO_H
#define LAB5_II_FILEREPO_H

#include "Repo.h"
#include "../Domain/Scooter.h"

#include <memory>
#include <algorithm>
#include <string>
#include <filesystem>
#include <fstream>
#include <map>

using namespace std;

template<class Obj>
class FileRepo : public Repo<Obj> {

protected:
    string filepath;
    std::map<domain::State, std::string> stateMap{
            {domain::State::reserved,   "reserved"},
            {domain::State::parked,     "parked"},
            {domain::State::in_service, "in_service"},
            {domain::State::out_of_use, "out_of_use"},
            {domain::State::in_use,     "in_use"},
    };
public:

    virtual string list_to_string(vector<shared_ptr<Obj>> &obj_list) = 0;

    virtual vector<shared_ptr<Obj>> to_obj_list(string) = 0;

    virtual void create_new_file() = 0;

    explicit FileRepo(string &path) {
        filepath = path;
    }

    void save(vector<shared_ptr<Obj>> &obj_list) {
        string obj_list_str = list_to_string(obj_list);
        write_to_file(obj_list_str);
    }

    void write_to_file(string &content) {
        ofstream file(filepath);
        file << content;
        file.close();
    }

    string read_from_file() {
        //string content;
        ifstream file(filepath);
        if (!file) {
            std::cerr << "Error opening the file."<<std::endl;
            create_new_file();

            return "";
        }
        std::string content;
        std::string line;
        while (getline(file, line)) {
            line += "\n";
            content += line;
        }
        content.erase(content.length() - 1);
        file.close();
        return content;
    }

    bool add(shared_ptr<Obj> obj_ptr) override {
        /*
        input pointer of Obj obj
        output: false, if ObjObj with same id as Obj_ptr exists
                true, if added successfully
        */

        //read list from file

        vector<shared_ptr<Obj>> obj_list = find_all();

        for (auto it = obj_list.begin(); it != obj_list.end(); it++) {
            if ((*it)->get_id() == (*obj_ptr).get_id()) {
                return false;
            }
        }
        //if not, add the Obj
        obj_list.push_back(obj_ptr);
        save(obj_list);
        return true;
    }


    bool remove(string id) override {
//output: true if Obj found and removed successfully,
//        else false

        vector<shared_ptr<Obj>> obj_list = find_all();

        for (auto it = obj_list.begin(); it != obj_list.end(); it++) {
            if ((*it)->get_id() == id) {
                obj_list.erase(it);
                save(obj_list);
                return true;
            }
        }
        return false;
    }

    bool update(shared_ptr<Obj> Obj_ptr) override {
//output: true if Obj with same id exists
//        false if Obj not updated successfully because Obj with same id as Obj_ptr doesnt exist

        if (remove(Obj_ptr->get_id())) {
            add(Obj_ptr);
            return true;
        }
        return false;
    }

    vector<shared_ptr<Obj>> find_all() override {
        string filecontent = read_from_file();
        return to_obj_list(filecontent);
    }
};


#endif //LAB5_II_FILEREPO_H
