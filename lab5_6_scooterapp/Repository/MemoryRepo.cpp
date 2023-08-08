//
// Created by Maria on 5/21/2023.
//

#include "MemoryRepo.h"
#include <algorithm>
//#include "../Domain/Obj.h"


namespace memoryrepo{

    template<class Obj>
    MemoryRepo<Obj>::MemoryRepo() {}

    template<class Obj>
    bool MemoryRepo<Obj>::add(shared_ptr<Obj> Obj_ptr) {
        /*
        input pointer of Obj obj
        output: false, if ObjObj with same id as Obj_ptr exists
                true, if added successfully
        */

        for (auto it = obj_list.begin(); it != obj_list.end(); it++) {
            if ((*it)->get_id() == (*Obj_ptr).get_id()) {
                return false;
            }
        }
        //if not, add the Obj
        obj_list.push_back(Obj_ptr);
        return true;
    }

    template<class Obj>
    bool MemoryRepo<Obj>::remove(string id) {
        //output: true if Obj found and removed successfully,
        //        else false

        for (auto it = obj_list.begin(); it != obj_list.end(); it++) {
            if ((*it)->get_id() == id) {
                obj_list.erase(it);
                return true;
            }
        }
        return false;
    }

    template<class Obj>
    bool MemoryRepo<Obj>::update(shared_ptr<Obj> Obj_ptr) {
        //output: true if Obj with same id exists
        //        false if Obj not updated successfully because Obj with same id as Obj_ptr doesnt exist

        if(remove_Obj(Obj_ptr->get_id())==true) {
            add_Obj(Obj_ptr);
            return true;
        }
        return false;
    }

    template<class Obj>
    vector<shared_ptr<Obj>> MemoryRepo<Obj>::find_all() {
        return obj_list;
    }
}
