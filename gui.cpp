#include "gui.h"
#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QFrame>
#include <QWidget>
#include "teacherui.h"

gui::gui(QWidget *parent, Controller* ctrl) : QMainWindow(parent)
{
    m_controller = ctrl;
    this->setWindowTitle("QUIZ");
    this->setMinimumSize(QSize(400, 200));

    QWidget* centralW = createCentralWidget();
    this->setCentralWidget(centralW);
}

void gui::openTeacherWindow()
{
    teacherWindow = new teacherUI(this, m_controller);
    teacherWindow->show();
}

void gui::openStudentWindow()
{
    studentWindow = new studentui(this, m_controller);
    studentWindow->show();
}

QWidget *gui::createCentralWidget()
{
    QWidget* widget = new QWidget(this);
    QGridLayout* grid = new QGridLayout(this);
    QLabel* label1 = new QLabel("Choose mode", this);

    QPushButton* teacherBtn = new QPushButton("Teacher Mode", this);
    QPushButton* studentBtn = new QPushButton("Student Mode", this);

    grid->addWidget(label1, 0, 1);
    grid->addWidget(teacherBtn, 1, 0);
    grid->addWidget(studentBtn, 1, 2);

    widget->setLayout(grid);

    connect(teacherBtn, &QPushButton::clicked, this, &gui::openTeacherWindow);
    connect(studentBtn, &QPushButton::clicked, this, &gui::openStudentWindow);

    return widget;
}
