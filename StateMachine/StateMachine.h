#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <iostream>

// Forward declarations
class EmbeddedSystemX;
class Failure;
class Initializing;

// Base State Class
class State {
public:
    virtual ~State() {}
    virtual void SystemSelftest(EmbeddedSystemX*) {}
    virtual void Restart(EmbeddedSystemX*) {}
    virtual void Initialized(EmbeddedSystemX*) {}

    static void ChangeState(EmbeddedSystemX* context, State* newState);
};

// Concrete State: PowerOnSelfTest
class PowerOnSelfTest : public State {
public:
    static PowerOnSelfTest* getInstance();
    void SystemSelftest(EmbeddedSystemX* context) override;
};

// Concrete State: Failure
class Failure : public State {
public:
    static Failure* getInstance();
    void Restart(EmbeddedSystemX* context) override;
};

// Concrete State: Initializing
class Initializing : public State {
public:
    static Initializing* getInstance();
    void Initialized(EmbeddedSystemX* context) override;
};

// EmbeddedSystemX Context Class
class EmbeddedSystemX {
private:
    State* currentState;

public:
    EmbeddedSystemX();
    void setState(State* newState);
    void SystemSelftest();
    void Restart();
    void Initialized();
};

#endif // STATEMACHINE_H
