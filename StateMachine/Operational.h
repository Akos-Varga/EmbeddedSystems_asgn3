#ifndef OPERATIONAL_H
#define OPERATIONAL_H

#include <iostream>

// Command Base Class
class Operational;
class Command {
public:
    virtual ~Command() {}
    virtual void execute(Operational* context) = 0;
};

// Forward declaration of all state classes
class OpState;
class Ready;
class Configuration;
class RTL;
class Suspended;

class Operational {
private:
    OpState* currentOpState;
    friend class OpState;
    void setOpState(OpState* newState) { currentOpState = newState; }

public:
    Operational();
    void changeState(OpState* newState); // Public state change method

    // Events
    void Configure();
    void ConfEnd();
    void Stop();
    void StopRTL();
    void Start();
    void Suspend();
    void Resume();
};

// Base State Class
class OpState {
public:
    virtual ~OpState() {}

    virtual void Configure(Operational*) {}
    virtual void ConfEnd(Operational*) {}
    virtual void Stop(Operational*) {}
    virtual void StopRTL(Operational*) {}
    virtual void Start(Operational*) {}
    virtual void Suspend(Operational*) {}
    virtual void Resume(Operational*) {}

protected:
    void ChangeOpState(Operational* context, OpState* newOpState) {
        context->setOpState(newOpState);
    }
};

// Concrete States
class Ready : public OpState {
private:
    static Ready* instance;
    Ready() {}

public:
    static Ready* getInstance();
    void Configure(Operational* context) override;
    void Start(Operational* context) override;
};

class Configuration : public OpState {
private:
    static Configuration* instance;
    Configuration() {}

public:
    static Configuration* getInstance();
    void ConfEnd(Operational* context) override;
};

class RTL : public OpState {
private:
    static RTL* instance;
    RTL() {}

public:
    static RTL* getInstance();
    void StopRTL(Operational* context) override;
    void Suspend(Operational* context) override;
};

class Suspended : public OpState {
private:
    static Suspended* instance;
    Command* resumeCommand;
    Command* stopCommand;

    Suspended() : resumeCommand(nullptr), stopCommand(nullptr) {}

public:
    static Suspended* getInstance();
    ~Suspended();

    void setResumeCommand(Command* command);
    void setStopCommand(Command* command);

    void Stop(Operational* context) override;
    void Resume(Operational* context) override;
};

// Commands
class ResumeCommand : public Command {
public:
    void execute(Operational* context) override;
};

class StopCommand : public Command {
public:
    void execute(Operational* context) override;
};

#endif
