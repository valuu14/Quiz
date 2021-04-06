#ifndef LAB7_TESTCONTROLLER_H
#define LAB7_TESTCONTROLLER_H

#include "controller.h"
#include "string"
#include <cassert>

class testController {
public:

    static void testAdd();
    static void testRemove();
    static void testUpdate();
    static void testAllShuffled();
    static void testFilterQuestions();
    static void testRun();

private:
    Controller ctrl;
//    static void tearDown();
//    static Controller setUp();
};


#endif //LAB7_TESTCONTROLLER_H
