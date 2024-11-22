#include "StateMachine.h"

int main() {
    EmbeddedSystemX system;

    system.SystemSelftest(); // Triggers self-test, moves to Failure state
    system.Restart();        // Restarts system, moves back to PowerOnSelfTest

    return 0;
}