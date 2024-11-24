#include "StateMachine.h"

// State Transition Helper
void State::ChangeState(EmbeddedSystemX* context, State* newState) {
    context->setState(newState);
}

// PowerOnSelfTest Singleton Instance
PowerOnSelfTest* PowerOnSelfTest::getInstance() {
    static PowerOnSelfTest instance;
    return &instance;
}

void PowerOnSelfTest::SystemSelftest(EmbeddedSystemX* context) {
    char userInput;
    std::cout << "Performing system self-test...\n";
    std::cout << "Enter result (p/f):";
    std::cin >> userInput;

    if(userInput == 'p'){
        std::cout << "Self-test pass! Transitioning to Initialization state.\n";
        ChangeState(context, Initializing::getInstance());
    }
    else {
        std::cout << "Self-test failed! Transitioning to Failure state.\n";
        ChangeState(context, Failure::getInstance());
    }

}

// Failure Singleton Instance
Failure* Failure::getInstance() {
    static Failure instance;
    return &instance;
}

void Failure::Restart(EmbeddedSystemX* context) {
    std::cout << "Restarting system... Transitioning back to PowerOnSelfTest.\n";
    ChangeState(context, PowerOnSelfTest::getInstance());
}

// Initializing Singleton Instance
Initializing* Initializing::getInstance() {
    static Initializing instance;
    return &instance;
}

void Initializing::Initialized(EmbeddedSystemX* context) {
    std::cout << "System Initialized... Transitioning to Operational mode.\n";
    // ChangeState(context, PowerOnSelfTest::getInstance());
}

// EmbeddedSystemX Definitions
EmbeddedSystemX::EmbeddedSystemX() : currentState(PowerOnSelfTest::getInstance()) {}

void EmbeddedSystemX::setState(State* newState) {
    currentState = newState;
}

void EmbeddedSystemX::SystemSelftest() {
    currentState->SystemSelftest(this);
}

void EmbeddedSystemX::Restart() {
    currentState->Restart(this);
}

void EmbeddedSystemX::Initialized() {
    currentState->Initialized(this);
}