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
    std::cout << "Performing system self-test...\n";
    std::cout << "Self-test failed! Transitioning to Failure state.\n";
    ChangeState(context, Failure::getInstance());
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