#include "testrepository.h"

void testRepository::testAdd() {
    //setup
    Repository r;
    std::string id = "1", text = "Is this a question?", sub = "random", type = "T/F", p_a[3], c_a = "True";
    p_a[0] = "True"; p_a[1] = "False";
    Question q(id, text, sub, type, p_a, c_a);

    assert(r.add(&q));
    assert(!r.add(&q));
}

void testRepository::testRemove() {
    //setup
    Repository r;
    std::string id = "1", text = "Is this a question?", sub = "random", type = "T/F", p_a[3], c_a = "True";
    p_a[0] = "True"; p_a[1] = "False";
    Question q(id, text, sub, type, p_a, c_a);
    r.add(&q);

    assert(r.remove(id));
    assert(!r.remove(id));
}

void testRepository::testUpdate() {
    //setup
    Repository r;
    std::string id = "1", text = "Is this a question?", sub = "random", type = "T/F", p_a[3], c_a = "True";
    p_a[0] = "True"; p_a[1] = "False";
    Question q(id, text, sub, type, p_a, c_a);
    r.add(&q);

    assert(r.update(id, sub, type, p_a, c_a));
    id = "2";
    assert(!r.update(id, sub, type, p_a, c_a));
}

void testRepository::testRun() {
    testAdd();
    testRemove();
    testUpdate();
}
