#ifndef GUI_H
#define GUI_H
#include "controller.h"
#include "teacherui.h"
#include "studentui.h"
#include <QLineEdit>
#include <QMainWindow>
#include <QListWidget>

class gui: public QMainWindow
{

signals:

public slots:
    void openTeacherWindow();
    void openStudentWindow();
public:
    explicit gui(QWidget *parent = nullptr, Controller* ctrl = nullptr);
   // ~gui();

private:
    QWidget *createCentralWidget();

    Controller* m_controller;
    teacherUI* teacherWindow;
    studentui* studentWindow;
};

#endif // GUI_H
