#ifndef LAB5_II_MEMORYREPO_H
#define LAB5_II_MEMORYREPO_H

#include "Repo.h"

#include <vector>
#include <string>
#include <memory>

using namespace std;

namespace memoryrepo {

    template<class Obj>
    class MemoryRepo : public Repo<Obj> {
    private:
        vector<shared_ptr<Obj>> obj_list;

    public:

        bool add(shared_ptr<Obj> Obj_ptr) override {
            /*
            input pointer of obj
            output: false, if ObjObj with same id as Obj_ptr exists
                    true, if added successfully
            */
            for (auto it = obj_list.begin(); it != obj_list.end(); it++) {
                if ((*it)->get_id() == (*Obj_ptr).get_id()) {
                    return false;
                }
            }
            //if not, add obj
            obj_list.push_back(Obj_ptr);
            return true;
        }

        bool remove(string id) override {
            /*
            output: true if Obj found and removed successfully,
                    else false
            */
            for (auto it = obj_list.begin(); it != obj_list.end(); it++) {
                if ((*it)->get_id() == id) {
                    obj_list.erase(it);
                    return true;
                }
            }
            return false;
        }

        bool update(shared_ptr<Obj> Obj_ptr) override {
            /*
            output: true if Obj with same id exists
                    false if Obj not updated successfully because Obj with same id as Obj_ptr doesnt exist
            */
            if (remove(Obj_ptr->get_id()) == true) {
                add(Obj_ptr);
                return true;
            }
            return false;
        }

        vector<shared_ptr<Obj>> find_all() override {
            return obj_list;
        }

    };
}


#endif //LAB5_II_MEMORYREPO_H
