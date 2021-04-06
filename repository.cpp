#include <iostream>
#include "repository.h"

Repository::Repository(const Repository &r) {
    for (int i = 0; i < this->elems.size(); i++){
        this->elems[i] = r.elems[i];
    }
}

void Repository::toString(std::string& str) {
    for (auto & elem : this->elems){
        elem->toString(str);
    }
}

bool Repository::add(Question *q) {
    int res = find(q->getId());
    if (res == -1){
        elems.push_back(q);
        return true;
    }
    return false;
}

int Repository::find(std::string id) {
    int i = 0;
    while (i < elems.size()){
        if (this->elems[i]->getId() == id) return i;
        i++;
    }
    return -1;
}

bool Repository::remove(std::string id) {
    int res = find(id);
    if (res != -1){
        this->elems.erase(this->elems.begin() + res);
        return true;
    }
    return false;
}

bool Repository::update(std::string id, std::string s, std::string t, std::string *p_a, std::string c_a) {
    int res = find(id);
    if (res != -1){
        if (!s.empty()) this->elems[res]->setSubject(s);
        if(!t.empty()) this->elems[res]->setType(t);
        if(!p_a[0].empty()) this->elems[res]->setPossibleAnswers(p_a);
        if(!c_a.empty()) this->elems[res]->setCorrectAnswer(c_a);
        return true;
    }
    return false;
}

void Repository::getAll(std::vector<Question *> &v) {
    for (auto &q : this->elems){
        v.push_back(q);
    }
}

void Repository::filterBySubject(std::string sub, std::vector<Question*> &filteredList) {
    if (sub.empty()) getAll(filteredList);
    else
        for (auto &q : this->elems){
            if ((*q).getSubject() == sub) filteredList.push_back(q);
        }
}
