// CREATED AND OWNED BY: Meruzhan Sargsyan
// ALL COPYRIGHT LAWS in LICENSE APPLY

#ifndef TESTER_HPP
#define TESTER_HPP

#include <vector>
#include <functional>
#include <string>
#include <iostream>

namespace ST {

class Tester {
    using Test = std::function<bool()>;
    public:
    Tester() : name{"Anonymous Tester"}, outStream{std::cout} {};

    Tester(const std::string& aName) : name{aName}, outStream{std::cout} {};

    Tester(std::ostream& aStream) : name{"Anonymous Tester"}, outStream{aStream} {};

    Tester(const std::string& aTesterName, std::ostream& aStream) : name{aTesterName}, outStream{aStream} {};

    template <typename Func, typename... Args>
        void registerTest(const std::string& aName, Func&& aFunc, Args&&... anArgs) {
#if __cplusplus >= 201703L
            static_assert(std::is_invocable_v<Func,Args...>, "Parameter not compatable with types!\n");

            using ReturnType = std::invoke_result_t<Func, Args...>;
            static_assert(std::is_convertible_v<ReturnType,bool>, "Invalid return type!\n");
#else
            static_assert(std::is_convertible<typename std::result_of<Func(Args...)>::type, bool>::value,
                  "Invalid return type!");
#endif

            auto theBinding = std::bind(std::forward<Func>(aFunc), std::forward<Args>(anArgs)...);
            tests.emplace_back(aName, theBinding);

            ++testCount;
        }

    bool runTests() {
        outStream << "\n---------------------------------------------\n";
        outStream << "Tester " + name + " is running;\n";

        size_t theTotalPassed = 0;

        for(auto [theName, theTest] : tests) {
            outStream << "\nRunning " << theName << " test\n";
            bool theResult = theTest();
            if(theResult) ++theTotalPassed;

            outStream << "Test " << theName << " result: " << (theResult ? "\u001b[32m PASS" : "\u001b[31m FAIL") << "\u001b[0m \n";
        }

        outStream << "\nPASSED " << theTotalPassed << '/' << testCount << " Test(s)\n";
        outStream << "---------------------------------------------\n";

        return static_cast<int>(theTotalPassed) == testCount;
    }

    private:
    std::string name;
    int testCount = 0;
    std::ostream& outStream;
    std::vector<std::pair<std::string,Test>> tests;
};

}

#endif
