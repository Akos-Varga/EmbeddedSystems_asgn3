#include "Operational.h"

// Helper Function
void Operational::changeState(OpState* newState) {
    currentOpState = newState;
}

// Ready State
Ready* Ready::instance = nullptr;
Ready* Ready::getInstance() {
    if (!instance) instance = new Ready();
    return instance;
}

void Ready::Configure(Operational* context) {
    std::cout << "Configuring the system.\n";
    ChangeOpState(context, Configuration::getInstance());
}

void Ready::Start(Operational* context) {
    std::cout << "Starting the Real Time Loop.\n";
    ChangeOpState(context, RTL::getInstance());
}

// Configuration State
Configuration* Configuration::instance = nullptr;
Configuration* Configuration::getInstance() {
    if (!instance) instance = new Configuration();
    return instance;
}

void Configuration::ConfEnd(Operational* context) {
    std::cout << "Configuration ended.\n";
    ChangeOpState(context, Ready::getInstance());
}

// RTL Loop State
RTL* RTL::instance = nullptr;
RTL* RTL::getInstance() {
    if (!instance) instance = new RTL();
    return instance;
}

void RTL::StopRTL(Operational* context) {
    std::cout << "Loop stopped.\n";
    ChangeOpState(context, Ready::getInstance());
}

void RTL::Suspend(Operational* context) {
    std::cout << "Loop suspended.\n";
    ChangeOpState(context, Suspended::getInstance());
}

// Suspended State
Suspended* Suspended::instance = nullptr;
Suspended* Suspended::getInstance() {
    if (!instance) instance = new Suspended();
    return instance;
}

Suspended::~Suspended() {
    delete resumeCommand;
    delete stopCommand;
}

void Suspended::setResumeCommand(Command* command) {
    resumeCommand = command;
}

void Suspended::setStopCommand(Command* command) {
    stopCommand = command;
}

void Suspended::Stop(Operational* context) {
    if (stopCommand) {
        stopCommand->execute(context);
    }
    else {
        std::cerr << "Stop command not set!\n";
    }
}

void Suspended::Resume(Operational* context) {
    if (resumeCommand) {
        resumeCommand->execute(context);
    }
    else {
        std::cerr << "Resume command not set!\n";
    }
}

// Commands
void ResumeCommand::execute(Operational* context) {
    std::cout << "Resuming loop from Suspended state.\n";
    context->changeState(RTL::getInstance());
}

void StopCommand::execute(Operational* context) {
    std::cout << "Stopping system from Suspended state.\n";
    context->changeState(Ready::getInstance());
}

// Operational Constructor
Operational::Operational() : currentOpState(Ready::getInstance()) {}

void Operational::Configure() { currentOpState->Configure(this); }
void Operational::ConfEnd() { currentOpState->ConfEnd(this); }
void Operational::StopRTL() { currentOpState->StopRTL(this); }
void Operational::Start() { currentOpState->Start(this); }
void Operational::Suspend() { currentOpState->Suspend(this); }
void Operational::Resume() { currentOpState->Resume(this); }
void Operational::Stop() { currentOpState->Stop(this); }
