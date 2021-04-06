#ifndef LAB7_CONTROLLER_H
#define LAB7_CONTROLLER_H

#include "repository.h"
#include <fstream>
#include <string>
#include <QVector>
#include <vector>
#include <stack>

using namespace std;

class Controller {
public:
    Controller(Repository *r1, Repository *r2);
    Controller(const Controller& c);
    explicit Controller(Repository *r);

    ~Controller() = default;

    vector<Question*>& getQuestions(){
        return repo->getQuestions();
    }

    /**
     * @brief initialize the repository with 10 questions
     */
    void initValues();
    /**
     * @brief adds a question
     * @param q
     * @return true if the question was added successfully, false otherwise
     */
    bool addQuestion(Question *q, int i);
    /**
     * @brief deletes a question
     * @param id
     * @return true if the question was deleted successfully, false otherwise
     */
    bool removeQuestion(string id, int i);
    /**
     * @brief updates the subject, type, possAnswers and/or correctAnswer of a question by id
     * @param id
     * @param s
     * @param type
     * @param p_a
     * @param c_a
     * @return true if the question exists and was updated, false otherwise
     */
    bool updateQuestion(string id, string s, string type, string p_a[3], string c_a);
    /**
     * @brief gets the string representation
     * @param str
     */
    void printAll(string &str);
    /**
     * @brief gets all the questions and shuffles the answers(not yet implemented)
     * @param v
     * @param i
     */
    void getAllShuffled(std::vector<Question*> &v, int i);
    /**
     * @brief filters by a subject
     * @param sub
     * @param filteredList
     */
    void filterQuestions(std::string sub, std::vector<Question*> &filteredList);
    void saveData();

    int undoOp();
    int redoOp();

private:
    Repository* repo;
    Repository* reviewList;
    std::stack<Question*> undo;
    std::stack<Question*> redo;
    std::stack<int> operationUndo, operationRedo;
};


#endif //LAB7_CONTROLLER_H
