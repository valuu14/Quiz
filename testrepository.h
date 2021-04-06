#ifndef LAB7_TESTREPOSITORY_H
#define LAB7_TESTREPOSITORY_H

#include "repository.h"
#include "cassert"

class testRepository {
public:

    static void testAdd();
    static void testRemove();
    static void testUpdate();
    static void testRun();

private:
    Repository repo;
};


#endif //LAB7_TESTREPOSITORY_H
