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
void PowerOnSelfTest::SystemSelftest(EmbeddedSystemX* context) {
    std::cout << "Performing self-test...\n";
    char result;
    std::cout << "Enter test result (o for TestOk, f for TestFailed): ";
    std::cin >> result;
    if (result == 'o') {
        std::cout << "Self-test passed! Transitioning to Initializing state.\n";
        ChangeState(context, Initializing::getInstance());
    }
    else {
        std::cout << "Self-test failed! Transitioning to Failure state.\n";
        ChangeState(context, Failure::getInstance());
    }
}

// Failure State
Failure* Failure::instance = nullptr;
Failure* Failure::getInstance() {
    if (!instance) instance = new Failure();
    return instance;
}
void Failure::Restart(EmbeddedSystemX* context) {
    std::cout << "Restarting system... Transitioning back to PowerOnSelfTest.\n";
    ChangeState(context, PowerOnSelfTest::getInstance());
}

// Initializing State
Initializing* Initializing::instance = nullptr;
Initializing* Initializing::getInstance() {
    if (!instance) instance = new Initializing();
    return instance;
}
void Initializing::StartInitializing(EmbeddedSystemX* context) {
    std::cout << "Initializing system...\n";
    ChangeState(context, Operational::getInstance());
}

// Operational State
Operational* Operational::instance = nullptr;
Operational* Operational::getInstance() {
    if (!instance) instance = new Operational();
    return instance;
}
void Operational::ConfigurationEnded(EmbeddedSystemX* context) {
    std::cout << "Configuration ended. Transitioning to Ready state.\n";
    ChangeState(context, Ready::getInstance());
}
void Operational::Exit(EmbeddedSystemX* context) {
    std::cout << "Exiting system...\n";
}

// Ready State
Ready* Ready::instance = nullptr;
Ready* Ready::getInstance() {
    if (!instance) instance = new Ready();
    return instance;
}
void Ready::Start(EmbeddedSystemX* context) {
    std::cout << "Starting system... Transitioning to RealTimeLoop state.\n";
    ChangeState(context, RealTimeLoop::getInstance());
}
void Ready::Stop(EmbeddedSystemX* context) {
    std::cout << "Stopping system...\n";
}

// RealTimeLoop State
RealTimeLoop* RealTimeLoop::instance = nullptr;
RealTimeLoop* RealTimeLoop::getInstance() {
    if (!instance) instance = new RealTimeLoop();
    return instance;
}
void RealTimeLoop::Stop(EmbeddedSystemX* context) {
    std::cout << "Stopping system...\n";
    ChangeState(context, Ready::getInstance());
}
void RealTimeLoop::Suspend(EmbeddedSystemX* context) {
    std::cout << "Suspending system...\n";
    ChangeState(context, Suspended::getInstance());
}

// Suspended State
Suspended* Suspended::instance = nullptr;
Suspended* Suspended::getInstance() {
    if (!instance) instance = new Suspended();
    return instance;
}
void Suspended::Resume(EmbeddedSystemX* context) {
    std::cout << "Resuming system... Transitioning to RealTimeLoop state.\n";
    ChangeState(context, RealTimeLoop::getInstance());
}

// EmbeddedSystemX Context Class
EmbeddedSystemX::EmbeddedSystemX() : currentState(PowerOnSelfTest::getInstance()) {}

void EmbeddedSystemX::SystemSelftest() { currentState->SystemSelftest(this); }
void EmbeddedSystemX::StartInitializing() { currentState->StartInitializing(this); }
void EmbeddedSystemX::ConfigurationEnded() { currentState->ConfigurationEnded(this); }
void EmbeddedSystemX::Start() { currentState->Start(this); }
void EmbeddedSystemX::Stop() { currentState->Stop(this); }
void EmbeddedSystemX::Suspend() { currentState->Suspend(this); }
void EmbeddedSystemX::Resume() { currentState->Resume(this); }
void EmbeddedSystemX::Restart() { currentState->Restart(this); }
void EmbeddedSystemX::Exit() { currentState->Exit(this); }
