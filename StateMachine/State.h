#ifndef STATE_H
#define STATE_H

#include "EmbeddedSystemX.h"

class PowerOnSelfTest;  // Forward declaration

// Base State Class
class State {
public:
    virtual ~State() {}

    // Event handling interface
    virtual void SelfTestFailed(EmbeddedSystemX*) {}
    virtual void Restart(EmbeddedSystemX*) {}
    virtual void SystemSelftest(EmbeddedSystemX*) {}

protected:
    void ChangeState(EmbeddedSystemX* context, State* newState);
};

// Concrete State: PowerOnSelfTest
class PowerOnSelfTest : public State {
private:
    static PowerOnSelfTest* instance;

    PowerOnSelfTest() {}

public:
    static PowerOnSelfTest* getInstance();  // Declare the getInstance method
    void SystemSelftest(EmbeddedSystemX* context) override;
};

#endif // STATE_H
