#ifndef REAL_TIME_LOOP_H
#define REAL_TIME_LOOP_H

#include <iostream>

// Forward declarations
class RealTimeLoop;
class Mode;

// RealTimeLoop class
class RealTimeLoop {
private:
    Mode* currentMode;  // Pointer to the current state

public:
    RealTimeLoop();

    void setMode(Mode* newMode);  // Transition to a new state

    void chmode1();
    void chmode2();
    void chmode3();
};

// Base State Class
class Mode {
public:
    virtual ~Mode() {}
    virtual void handleChmode1(RealTimeLoop* context) = 0;
    virtual void handleChmode2(RealTimeLoop* context) = 0;
    virtual void handleChmode3(RealTimeLoop* context) = 0;
};

// Mode1 State
class Mode1 : public Mode {
public:
    static Mode1* getInstance();

    void handleChmode1(RealTimeLoop* context) override;
    void handleChmode2(RealTimeLoop* context) override;
    void handleChmode3(RealTimeLoop* context) override;
};

// Mode2 State
class Mode2 : public Mode {
public:
    static Mode2* getInstance();

    void handleChmode1(RealTimeLoop* context) override;
    void handleChmode2(RealTimeLoop* context) override;
    void handleChmode3(RealTimeLoop* context) override;
};

// Mode3 State
class Mode3 : public Mode {
public:
    static Mode3* getInstance();

    void handleChmode1(RealTimeLoop* context) override;
    void handleChmode2(RealTimeLoop* context) override;
    void handleChmode3(RealTimeLoop* context) override;
};

#endif  // REAL_TIME_LOOP_H
#pragma once
