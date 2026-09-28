#include "RotaryEncoder.h"

void RotaryEncoder::setup() {
    pinMode(clk, INPUT_PULLUP);
    pinMode(dt, INPUT_PULLUP);

    attachInterruptArg(digitalPinToInterrupt(clk), updateEncoderInterrupt, this, CHANGE);
    attachInterruptArg(digitalPinToInterrupt(dt), updateEncoderInterrupt, this, CHANGE);
}

void RotaryEncoder::loop() {
    if (toUpdate) {
        toUpdate = false;
        updateEncoder();
    }
}

int RotaryEncoder::getPos() {
    return encoderPos;
}

void RotaryEncoder::setOnUpdateRotationCallback(void(*callback)(int)) {
    onUpdateRotation = callback;
}

void RotaryEncoder::setOnRotationUpCallback(void(*callback)()) {
    onRotationUp = callback;
}

void RotaryEncoder::setOnRotationDownCallback(void(*callback)()) {
    onRotationDown = callback;
}

void RotaryEncoder::updateEncoderInterrupt(void *argument) {
    auto* manager = static_cast<RotaryEncoder*>(argument);
    manager->toUpdate = true;
}

void RotaryEncoder::updateEncoder() {
    int MSB = digitalRead(clk);
    int LSB = digitalRead(dt);

    int encoded = (MSB << 1) | LSB;
    int sum = (lastEncoded << 2) | encoded;

    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
        encoderPos++;

        if (onRotationUp != nullptr) {
            onRotationUp();
        }
    }
    if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
        encoderPos--;

        if (onRotationDown != nullptr) {
            onRotationDown();
        }
    }

    lastEncoded = encoded;
    if (onUpdateRotation != nullptr) {
        onUpdateRotation(encoderPos);
    }
}
