#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <iostream>

// Forward declaration of EmbeddedSystemX
class EmbeddedSystemX;

// Base State Class
class State {
public:
    virtual ~State() {}

    // Event handling interface
    virtual void SelfTestFailed(EmbeddedSystemX*) {}
    virtual void SelfTestOK(EmbeddedSystemX*) {}
    virtual void RestartF(EmbeddedSystemX*) {}
    virtual void Exit(EmbeddedSystemX*) {}
    virtual void RestartO(EmbeddedSystemX*) {}
    virtual void Initialized(EmbeddedSystemX*) {}

protected:
    void ChangeState(EmbeddedSystemX* context, State* newState);
};

// Concrete States
class PowerOnSelfTest : public State {
private:
    static PowerOnSelfTest* instance;

    PowerOnSelfTest() {}

public:
    static PowerOnSelfTest* getInstance();
    void SelfTestFailed(EmbeddedSystemX* context) override;
    void SelfTestOK(EmbeddedSystemX* context) override;
};

class Failure : public State {
private:
    static Failure* instance;

    Failure() {}

public:
    static Failure* getInstance();
    void RestartF(EmbeddedSystemX* context) override;
    void Exit(EmbeddedSystemX* context) override;
};

class Initializing : public State {
private:
    static Initializing* instance;

    Initializing() {}

public:
    static Initializing* getInstance();
    void Initialized(EmbeddedSystemX* context) override;
};

class Operational : public State {
private:
    static Operational* instance;

    Operational() {}

public:
    static Operational* getInstance();
    void RestartO(EmbeddedSystemX* context) override;
};

// EmbeddedSystemX Context Class
class EmbeddedSystemX {
private:
    State* currentState;
    friend class State;
    void setState(State* newState) { currentState = newState; }

public:
    EmbeddedSystemX();

    // Events
    void SelfTestFailed();
    void SelfTestOK();
    void RestartF();
    void Exit();
    void RestartO();
    void Initialized();
};

#endif // STATEMACHINE_H



