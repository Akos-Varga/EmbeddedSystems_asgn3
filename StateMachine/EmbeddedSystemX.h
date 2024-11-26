#ifndef EMBEDDEDSYSTEMX_H
#define EMBEDDEDSYSTEMX_H

#include "State.h"

// Context Class
class EmbeddedSystemX {
private:
    State* currentState;

public:
    EmbeddedSystemX(); // Only declare the constructor here
    void setState(State* newState);
    void SystemSelftest();
    void Restart();
    void Stop();
    void Resume();
    void chmode1();
    void chmode2();
    void chmode3();
};

#endif // EMBEDDEDSYSTEMX_H

