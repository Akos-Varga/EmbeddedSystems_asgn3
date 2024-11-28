#include "RealTimeLoop.h"

// RealTimeLoop Implementation
RealTimeLoop::RealTimeLoop() : currentMode(Mode1::getInstance()) {}

void RealTimeLoop::setMode(Mode* newMode) {
    currentMode = newMode;
}

void RealTimeLoop::chmode1() {
    currentMode->handleChmode1(this);
}

void RealTimeLoop::chmode2() {
    currentMode->handleChmode2(this);
}

void RealTimeLoop::chmode3() {
    currentMode->handleChmode3(this);
}

// Mode1 Implementation
Mode1* Mode1::getInstance() {
    static Mode1 instance;
    return &instance;
}

void Mode1::handleChmode1(RealTimeLoop* context) {
    std::cout << "Mode1: Handling chmode1 (staying in Mode1).\n";
}

void Mode1::handleChmode2(RealTimeLoop* context) {
    std::cout << "Mode1: Transitioning to Mode2.\n";
    context->setMode(Mode2::getInstance());
}

void Mode1::handleChmode3(RealTimeLoop* context) {
    std::cout << "Mode1: Transitioning to Mode3.\n";
    context->setMode(Mode3::getInstance());
}

// Mode2 Implementation
Mode2* Mode2::getInstance() {
    static Mode2 instance;
    return &instance;
}

void Mode2::handleChmode1(RealTimeLoop* context) {
    std::cout << "Mode2: Transitioning to Mode1.\n";
    context->setMode(Mode1::getInstance());
}

void Mode2::handleChmode2(RealTimeLoop* context) {
    std::cout << "Mode2: Handling chmode2 (staying in Mode2).\n";
}

void Mode2::handleChmode3(RealTimeLoop* context) {
    std::cout << "Mode2: Transitioning to Mode3.\n";
    context->setMode(Mode3::getInstance());
}

// Mode3 Implementation
Mode3* Mode3::getInstance() {
    static Mode3 instance;
    return &instance;
}

void Mode3::handleChmode1(RealTimeLoop* context) {
    std::cout << "Mode3: Transitioning to Mode1.\n";
    context->setMode(Mode1::getInstance());
}

void Mode3::handleChmode2(RealTimeLoop* context) {
    std::cout << "Mode3: Transitioning to Mode2.\n";
    context->setMode(Mode2::getInstance());
}

void Mode3::handleChmode3(RealTimeLoop* context) {
    std::cout << "Mode3: Handling chmode3 (staying in Mode3).\n";
}
