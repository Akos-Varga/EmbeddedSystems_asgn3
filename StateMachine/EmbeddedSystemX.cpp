#include "EmbeddedSystemX.h"
#include "State.h"

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

void EmbeddedSystemX::Stop() {
    currentState->Stop(this);
}

void EmbeddedSystemX::Resume() {
    currentState->Resume(this);
}

void EmbeddedSystemX::chmode1() {
    currentState->chmode1(this);
}

void EmbeddedSystemX::chmode2() {
    currentState->chmode2(this);
}

void EmbeddedSystemX::chmode3() {
    currentState->chmode3(this);
}