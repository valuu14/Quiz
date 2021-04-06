#ifndef LAB7_REPOSITORY_H
#define LAB7_REPOSITORY_H

#include "question.h"
#include <vector>

class Repository {
public:
    Repository() = default;
    Repository(const Repository& r);

    ~Repository() = default;

    std::vector<Question*>& getQuestions(){
        return this->elems;
    }

    /**
     * @brief adds a new question to the repository
     * @param q - pointer to an object of type Question
     * @return true if the question has been added successfully, false otherwise
     */
    bool add(Question* q);
    /**
     * @brief finds a question by its id
     * @param id
     * @return the position where the question has been found, -1 if the question is not in the repository
     */
    int find(std::string id);
    /**
     * @brief deletes a question by id
     * @param id
     * @return true if the question has been deleted successfully, false otherwise
     */
    bool remove(std::string id);
    /**
     * @brief changes the fields of a question by id
     * @param id
     * @param s - std::string, if empty nothing changes
     * @param t - std::string, if empty nothing changes
     * @param p_a - std::string, if empty nothing changes
     * @param c_a - std::string, if empty nothing changes
     * @return true if the operation was successful, false otherwise
     */
    bool update(std::string id, std::string s, std::string t, std::string p_a[3], std::string c_a);

    /**
     * @brief creates the string representation of an array of questions
     * @param str - stores the representation
     */
    void toString(std::string& str);
    /**
     * @brief well, it's just a getter
     * @param v
     */
    void getAll(std::vector<Question*> &v);
    /**
     * @brief adds every question that has the given subject to the 'filteredList'
     * @param sub
     * @param filteredList
     */
    void filterBySubject(std::string sub, std::vector<Question*> &filteredList);

    Question* getElement(std::string id){
        for(auto q : elems)
            if (q->getId() == id) return q;
        return nullptr;
    }
private:
    std::vector<Question*> elems;
};


#endif //LAB7_REPOSITORY_H
