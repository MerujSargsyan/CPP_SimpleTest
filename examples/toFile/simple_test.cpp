#include <SimpleTester.hpp>
#include <iostream>
#include <fstream>

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

    std::ofstream theOutFile{"./artifs/simple_test.txt", std::ios::trunc | std::ios::out};

    ST::Tester theTester{"Simple Tester >> File", theOutFile};
    theTester.registerTest("Test1", passingTest1);
    theTester.registerTest("Test2", passingTest2);
    theTester.registerTest("Test3", failingTest3);
    theTester.registerTest("Test4", inputTest, 10, 10);

    theTester.runTests();

    std::cout << "Testing Done! Check artifs/simple_test.txt\n";

    return 0;
}
