#pragma once

#include "Arduino.h"

class RotaryEncoder {
public:
    RotaryEncoder() {
        setup();
    }

    void setup();
    void loop();
    int getPos();
    void setOnUpdateRotationCallback(void (*callback)(int));
    void setOnRotationUpCallback(void (*callback)());
    void setOnRotationDownCallback(void (*callback)());

private:
    const int clk = D8;
    const int dt = D9;
    const int sw = D10;
    const int perIndent = 4;

    int encoderPos = 0;

    volatile uint8_t lastEncoded = 0;
    volatile int8_t transitionAccumulator = 0;
    volatile int pendingSteps = 0;

    void (*onUpdateRotation)(int) = nullptr;
    void (*onRotationUp)() = nullptr;
    void (*onRotationDown)() = nullptr;

    static void ARDUINO_ISR_ATTR updateEncoderInterrupt(void *argument);
    void ARDUINO_ISR_ATTR updateEncoder();
};
