#include "controller.h"
#include "customexception.h"
#include "persistenceengine.h"
#include <iostream>
#include <QString>
#include <vector>
#include <QtDebug>

Controller::Controller(Repository *r1, Repository *r2) {
    this->repo = r1;
    this->reviewList = r2;
}

Controller::Controller(const Controller &c) {
    this->repo = c.repo;
    this->reviewList = c.reviewList;
}

Controller::Controller(Repository *r) {
    this->repo = r;
}

bool Controller::addQuestion(Question *q, int i) {
    if (i == 1) {
        undo.push(q);
        operationUndo.push(1);
        return this->repo->add(q);
    }
    else return this->reviewList->add(q);
}

bool Controller::removeQuestion(string id, int i) {
     if (i == 1) {
         undo.push(repo->getElement(id));
         operationUndo.push(2);
         return this->repo->remove(id);
     }
     else return this->reviewList->remove(id);
}

bool Controller::updateQuestion(string id, string s, string type, string *p_a, string c_a) {
    return this->repo->update(id, s, type, p_a, c_a);
}

void Controller::initValues() {
//    std::ifstream f(R"(C:\University\OOP\qtProjects\lab7 - Copy\in.txt)");
//    std::string id, text, subject, type, p_a[3], c_a;
//    if (!f.is_open()) {
//        IOException e;
//        throw e;
//    }
//    else{
//        while (!f.eof()){
//            getline(f, id);
//            getline(f, text);
//            getline(f, subject);
//            getline(f, type);
//            if (type == "T/F"){
//                getline(f, p_a[0]);
//                getline(f, p_a[1]);
//            }
//            else {
//                getline(f, p_a[0]);
//                getline(f, p_a[1]);
//                getline(f, p_a[2]);
//            }
//            getline(f, c_a);
//            auto *q = new Question;
//            q->setId(id);
//            q->setText(text);
//            q->setSubject(subject);
//            q->setType(type);
//            q->setPossibleAnswers(p_a);
//            q->setCorrectAnswer(c_a);
//            this->addQuestion(q, 1);
//        }
//    }
//    f.close();
    PersistenceEngineJSON obj;
    obj.load(R"(C:\University\OOP\qtProjects\lab7gui\data.json)", this);
}

void Controller::printAll(string &str) {
    this->repo->toString(str);
}

void Controller::getAllShuffled(vector<Question *> &v, int i) {
    if (i == 1){
         this->repo->getAll(v);
    }
    else this->reviewList->getAll(v);
}

void Controller::filterQuestions(std::string sub, std::vector<Question*> &filteredList) {
    this->repo->filterBySubject(sub, filteredList);
}

void Controller::saveData() {
//    PersistenceEngineCSV obj;
//    QString qstr = "C:\\University\\OOP\\qtProjects\\lab7 - Copy\\data.csv";
//    std::vector <Question*> v;
//    this->getAllShuffled(v, 1);
//    if(obj.save(v, qstr)) std::cout << "A mers";
    PersistenceEngineJSON obj;
    QString qstr = "C:\\University\\OOP\\qtProjects\\lab7 - Copy\\data.json";
    std::vector <Question*> v;
    this->getAllShuffled(v, 1);
    if(obj.save(v, qstr)) std::cout << "da";
}

int Controller::undoOp()
{
    if (operationUndo.top() == 1){
        operationUndo.pop();
        operationRedo.push(1);
        Question* q = new Question;
        q = undo.top();
        repo->remove(q->getId());
        undo.pop();
        redo.push(q);
        return 1;
    }
    else {
        operationUndo.pop();
        operationRedo.push(2);
        Question* q = new Question;
        q = undo.top();
        repo->add(q);
        undo.pop();
        redo.push(q);
        return 2;
    }
}

int Controller::redoOp()
{
    if (operationRedo.top() == 1){
        Question* q = new Question;
        q = redo.top();
        repo->add(q);
        redo.pop();
        return 1;
    }
    else{
        Question* q = new Question;
        q = redo.top();
        repo->remove(q->getId());
        redo.pop();
        return 2;
    }
}
