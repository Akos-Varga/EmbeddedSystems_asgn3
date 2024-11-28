#include "StateMachine.h"

// Helper Function
void State::ChangeState(EmbeddedSystemX* context, State* newState) {
    context->setState(newState);
}

// PowerOnSelfTest State
PowerOnSelfTest* PowerOnSelfTest::instance = nullptr;
PowerOnSelfTest* PowerOnSelfTest::getInstance() {
    if (!instance) instance = new PowerOnSelfTest();
    return instance;
}
void PowerOnSelfTest::SelfTestOK(EmbeddedSystemX* context) {
        std::cout << "Self-test passed! Transitioning to Initializing state.\n";
        ChangeState(context, Initializing::getInstance());
}
void PowerOnSelfTest::SelfTestFailed(EmbeddedSystemX* context) {
    std::cout << "Self-test failed! Transitioning to Failure state.\n";
    ChangeState(context, Failure::getInstance());
}

// Failure State
Failure* Failure::instance = nullptr;
Failure* Failure::getInstance() {
    if (!instance) instance = new Failure();
    return instance;
}
void Failure::RestartF(EmbeddedSystemX* context) {
    std::cout << "Restarting system... Transitioning back to PowerOnSelfTest.\n";
    ChangeState(context, PowerOnSelfTest::getInstance());
}
void Failure::Exit(EmbeddedSystemX* context) {
    std::cout << "Exiting program.\n";
}

// Initializing State
Initializing* Initializing::instance = nullptr;
Initializing* Initializing::getInstance() {
    if (!instance) instance = new Initializing();
    return instance;
}
void Initializing::Initialized(EmbeddedSystemX* context) {
    std::cout << "System initialized...\n";
    ChangeState(context, Operational::getInstance());
}

// Operational State
Operational* Operational::instance = nullptr;
Operational* Operational::getInstance() {
    if (!instance) instance = new Operational();
    return instance;
}
void Operational::RestartO(EmbeddedSystemX* context) {
    std::cout << "Restarting system...\n";
    ChangeState(context, PowerOnSelfTest::getInstance());
}

// EmbeddedSystemX Context Class
EmbeddedSystemX::EmbeddedSystemX() : currentState(PowerOnSelfTest::getInstance()) {}

void EmbeddedSystemX::SelfTestFailed() { currentState->SelfTestFailed(this); }
void EmbeddedSystemX::SelfTestOK() { currentState->SelfTestOK(this); }
void EmbeddedSystemX::RestartF() { currentState->RestartF(this); }
void EmbeddedSystemX::Exit() { currentState->Exit(this); }
void EmbeddedSystemX::Initialized() { currentState->Initialized(this); }
void EmbeddedSystemX::RestartO() { currentState->RestartO(this); }
