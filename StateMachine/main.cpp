#include "StateMachine.h"
// #include "Operational.h"
// #include "RealTimeLoop.h"

int main() {
    
    // ============ Testing State Machine ============

    EmbeddedSystemX system;

    system.SelfTestOK();
    system.Initialized();
    system.RestartO();
    system.SelfTestFailed();
    system.RestartF();
    system.SelfTestFailed();
    system.Exit();

    
    // ============ Testing operational state ============
    
    // Create Operational context
    /*Operational operationalSystem;

    // Set up the Suspended state's commands
    Suspended* suspendedState = Suspended::getInstance();
    suspendedState->setResumeCommand(new ResumeCommand());
    suspendedState->setStopCommand(new StopCommand());

    // Simulate state transitions and events
    std::cout << "=== Testing State Transitions ===\n";

    // Transition to Configuration and Ready states
    operationalSystem.Configure();  // From Ready to Configuration
    operationalSystem.ConfEnd();    // From Configuration to Ready

    // Start the RTL loop
    operationalSystem.Start();      // From Ready to RTL

    // Suspend the RTL loop
    operationalSystem.Suspend();    // From RTL to Suspended

    // Test Resume command
    std::cout << "\n=== Testing Resume Command ===\n";
    operationalSystem.Resume();     // From Suspended to RTL

    // Test Stop command
    std::cout << "\n=== Testing Stop Command ===\n";
    operationalSystem.Suspend();    // From RTL to Suspended
    operationalSystem.Stop();       // From Suspended to Ready

    // End of test
    std::cout << "\n=== Test Completed ===\n";*/

    // ============ Testing Real Time Loop ============

    /*RealTimeLoop rtl;

    std::cout << "\n=== Testing Real Time Loop ===\n";

    rtl.chmode1();  // Mode1 -> Mode1
    rtl.chmode2();  // Mode1 -> Mode2
    rtl.chmode2();  // Mode2 -> Mode2
    rtl.chmode3();  // Mode2 -> Mode3
    rtl.chmode1();  // Mode3 -> Mode1*/

    return 0;
}
