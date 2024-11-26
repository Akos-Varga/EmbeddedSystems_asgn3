#include "State.h"
#include <iostream>

// Define the getInstance function here
PowerOnSelfTest* PowerOnSelfTest::instance = nullptr;

PowerOnSelfTest* PowerOnSelfTest::getInstance() {
    if (!instance) {
        instance = new PowerOnSelfTest();
    }
    return instance;
}

void PowerOnSelfTest::SystemSelftest(EmbeddedSystemX* context) {
    std::cout << "Performing system self-test...\n";
    std::cout << "Self-test failed! Transitioning to Failure state.\n";
    ChangeState(context, Failure::getInstance());
}
