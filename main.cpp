#include <QApplication>
#include <iostream>
#include "gui.h"
#include "ui.h"
#include "testcontroller.h"
#include "testrepository.h"
#include "customexception.h"
#include "persistenceengine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    testController::testRun();
    testRepository::testRun();

    Repository r;
    Controller ctrl{&r};
    ctrl.initValues();

    gui quizGUI(nullptr, &ctrl);
    quizGUI.show();

    return a.exec();
}
