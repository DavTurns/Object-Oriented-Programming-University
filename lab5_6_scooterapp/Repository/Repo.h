#ifndef LAB5_II_REPO_H
#define LAB5_II_REPO_H

#include <vector>
#include <memory>
#include <string>

template<class Obj>
class Repo {

public:
    virtual bool add(std::shared_ptr<Obj>) = 0;

    virtual bool remove(std::string id) = 0;

    virtual bool update(std::shared_ptr<Obj>) = 0;

    virtual std::vector<std::shared_ptr<Obj>> find_all() = 0;
};


#endif //LAB5_II_REPO_H
