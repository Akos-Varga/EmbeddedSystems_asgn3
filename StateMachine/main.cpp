#include "StateMachine.h"

int main() {
    EmbeddedSystemX system;

    system.SystemSelftest();    // Perform self-test (user decides outcome)
    system.StartInitializing(); // Transition to O
    system.ConfigurationEnded(); // Transition to Ready
    system.Start();             // Transition to RealTimeLoop
    system.Suspend();           // Transition to Suspended
    system.Resume();            // Back to RealTimeLoop
    system.Stop();              // Back to Ready
    system.Restart();           // Restart system

    return 0;
}
