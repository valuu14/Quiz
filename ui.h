#ifndef LAB7_UI_H
#define LAB7_UI_H

#include <iostream>
#include "controller.h"

class UI {
public:
    virtual ~UI() = default;
    virtual void printMenu() = 0;
    virtual void menu() = 0;
//    virtual void addQuestion() = 0;
//    virtual void deleteQuestion() = 0;
};

class TeacherUI: public UI{
public:
    explicit TeacherUI(Controller *c);
    ~TeacherUI() override = default;

    void menu() override;
    void printMenu() override;
    void addQuestion();
    void deleteQuestion();
    void showAll();
    void updateQuestion();

private:
    Controller *c;
};

class StudentUI: public UI{
public:
    explicit StudentUI(Controller *c);
    ~StudentUI() override = default;

    void menu() override;
    void secondMenu(Question* q, int &grade);
    void printMenu() override;
    static void printSecondMenu();
    void addQuestion(Question* q);
    void deleteQuestion();
    bool uiFilterQuestions();
    void app();
    static void chooseAnswer(Question* q, int &grade);
private:
    Controller *c;
};

#endif //LAB7_UI_H
