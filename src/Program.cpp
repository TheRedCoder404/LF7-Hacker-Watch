#include "Program.h"

#include <Arduino.h>

void Program::setup() {
    pinMode(rotarySw, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(rotarySw), &windowManager.onRotarySwitchPressed, FALLING);
}

void Program::loop() {
    windowManager.loop();
}
