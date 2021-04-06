#ifndef TEACHERUI_H
#define TEACHERUI_H
#include <QMainWindow>
#include <controller.h>
#include <QListWidget>
#include "addquestionteacher.h"
#include <QKeyEvent>


class teacherUI : public QMainWindow
{
public slots:
    void onPushButtonAdd();
    void onPushButtonDelete();

public:
    teacherUI(QWidget* parent = nullptr, Controller* ctrl = nullptr);
    void listPopulate();
    void keyPressEvent(QKeyEvent* event) override;

private:
    QWidget *createCentralWidget();

    Controller* m_controller;
    QListWidget* m_list;
    addQuestionTeacher* addWindow;
};

#endif // TEACHERUI_H
