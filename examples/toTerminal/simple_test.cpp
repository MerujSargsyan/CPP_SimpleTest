#include <SimpleTester.hpp>
#include <iostream>

bool passingTest1() {
    return 5 == 5;
}

bool passingTest2() {
    return true != false;
}

bool failingTest3() {
    return true == false;
}

bool inputTest(int a, int b) {
    return a == b;
}

int main(void) {
    std::cout << "Starting Testing\n";

    ST::Tester theTester{"Simple Tester"};
    theTester.registerTest("Test1", passingTest1);
    theTester.registerTest("Test2", passingTest2);
    theTester.registerTest("Test3", failingTest3);
    theTester.registerTest("Test4", inputTest, 10, 10);
    theTester.registerTest("Lambda", [](){return true;});

    theTester.runTests();

    return 0;
}
