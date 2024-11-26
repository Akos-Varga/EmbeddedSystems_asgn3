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
    virtual void SystemSelftest(EmbeddedSystemX*) {}
    virtual void StartInitializing(EmbeddedSystemX*) {}
    virtual void ConfigurationEnded(EmbeddedSystemX*) {}
    virtual void Start(EmbeddedSystemX*) {}
    virtual void Stop(EmbeddedSystemX*) {}
    virtual void Suspend(EmbeddedSystemX*) {}
    virtual void Resume(EmbeddedSystemX*) {}
    virtual void Restart(EmbeddedSystemX*) {}
    virtual void Exit(EmbeddedSystemX*) {}

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
    void SystemSelftest(EmbeddedSystemX* context) override;
};

class Failure : public State {
private:
    static Failure* instance;

    Failure() {}

public:
    static Failure* getInstance();
    void Restart(EmbeddedSystemX* context) override;
};

class Initializing : public State {
private:
    static Initializing* instance;

    Initializing() {}

public:
    static Initializing* getInstance();
    void StartInitializing(EmbeddedSystemX* context) override;
    //void Initialized(EmbeddedSystemX* context) override;
};

class Operational : public State {
private:
    static Operational* instance;

    Operational() {}

public:
    static Operational* getInstance();
    void ConfigurationEnded(EmbeddedSystemX* context) override;
    void Exit(EmbeddedSystemX* context) override;
};

class Ready : public State {
private:
    static Ready* instance;

    Ready() {}

public:
    static Ready* getInstance();
    void Start(EmbeddedSystemX* context) override;
    void Stop(EmbeddedSystemX* context) override;
};

class RealTimeLoop : public State {
private:
    static RealTimeLoop* instance;

    RealTimeLoop() {}

public:
    static RealTimeLoop* getInstance();
    void Stop(EmbeddedSystemX* context) override;
    void Suspend(EmbeddedSystemX* context) override;
};

class Suspended : public State {
private:
    static Suspended* instance;

    Suspended() {}

public:
    static Suspended* getInstance();
    void Resume(EmbeddedSystemX* context) override;
};

// EmbeddedSystemX Context Class
class EmbeddedSystemX {
private:
    State* currentState;

public:
    EmbeddedSystemX();
    void setState(State* newState) { currentState = newState; }

    // Events
    void SystemSelftest();
    void StartInitializing();
    void ConfigurationEnded();
    void Start();
    void Stop();
    void Suspend();
    void Resume();
    void Restart();
    void Exit();
};

#endif // STATEMACHINE_H



