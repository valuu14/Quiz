#include "testcontroller.h"

//void testController::tearDown() {
//
//}
//
//Controller testController::setUp() {
//    Repository r;
//    Controller ctrl(&r);
//    return ctrl;
//}

void testController::testAdd() {
    //setup
    Repository r;
    Controller ctrl{&r};

    std::string id = "1", text = "Is this a question?", sub = "random", type = "T/F", p_a[3], c_a = "True";
    p_a[0] = "True"; p_a[1] = "False";
    Question q(id, text, sub, type, p_a, c_a);
    ctrl.addQuestion(&q, 1);
    std::vector<Question*> l;
    ctrl.getAllShuffled(l, 1);

    assert(l[0]->getId() == "1");
    assert(!ctrl.addQuestion(&q, 1));
}

void testController::testRemove() {
    //setup
    Repository r;
    Controller ctrl{&r};

    std::string id = "1", text = "Is this a question?", sub = "random", type = "T/F", p_a[3], c_a = "True";
    p_a[0] = "True"; p_a[1] = "False";
    Question q(id, text, sub, type, p_a, c_a);
    ctrl.addQuestion(&q, 1);

    assert(ctrl.removeQuestion(id, 1));
    assert(!ctrl.removeQuestion(id, 1));
}

void testController::testUpdate() {
    //setup
    Repository r;
    Controller ctrl{&r};

    std::string id = "1", text = "Is this a question?", sub = "random", type = "T/F", p_a[3], c_a = "True";
    p_a[0] = "True"; p_a[1] = "False";
    Question q(id, text, sub, type, p_a, c_a);
    ctrl.addQuestion(&q, 1);

    assert(ctrl.updateQuestion(id, (std::string)"a", (std::string)"a", p_a, (std::string)"a"));
}

void testController::testAllShuffled() {
    //setup
    Repository r;
    Controller ctrl{&r};

    std::string id = "1", text = "Is this a question?", sub = "random", type = "T/F", p_a[3], c_a = "True";
    p_a[0] = "True"; p_a[1] = "False";
    std::vector<Question*> l;
    Question q(id, text, sub, type, p_a, c_a);
    id = "2"; text = "Is this a question2?", sub = "random2", type = "T/F";
    Question q2(id, text, sub, type, p_a, c_a);
    ctrl.addQuestion(&q, 1);
    ctrl.addQuestion(&q2, 1);
    ctrl.getAllShuffled(l, 1);

    assert(l[0]->getId() == "1");
    assert(l[1]->getId() == "2");
    assert(l[0]->getSubject() == "random");
    assert(l[1]->getSubject() == "random2");
}

void testController::testFilterQuestions() {
    //setup
    Repository r;
    Controller ctrl{&r};

    std::string id = "1", text = "Is this a question?", sub = "random", type = "T/F", p_a[3], c_a = "True";
    p_a[0] = "True"; p_a[1] = "False";
    std::vector<Question*> l;
    Question q(id, text, sub, type, p_a, c_a);
    id = "2"; text = "Is this a question2?", sub = "random2", type = "T/F";
    Question q2(id, text, sub, type, p_a, c_a);
    ctrl.addQuestion(&q, 1);
    ctrl.addQuestion(&q2, 1);
    ctrl.filterQuestions((std::string)"random", l);

    assert(l[0]->getSubject() == "random");
}

void testController::testRun() {
    testAdd();
    testRemove();
    testUpdate();
    testAllShuffled();
    testFilterQuestions();
}
