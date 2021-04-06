#ifndef ADDQUESTIONTEACHER_H
#define ADDQUESTIONTEACHER_H

#include <QMainWindow>
#include "controller.h"
#include <QLineEdit>

class addQuestionTeacher : public QMainWindow
{
public slots:
    void add();
public:
    addQuestionTeacher(Controller* ctrl, QMainWindow* parent = nullptr);
private:
    QWidget *createCentralWidget();

    Controller* m_controller;
    QLineEdit *id, *text, *subject, *type, *c_a;
    QLineEdit *p_a0, *p_a1, *p_a2;
};

#endif // ADDQUESTIONTEACHER_H
