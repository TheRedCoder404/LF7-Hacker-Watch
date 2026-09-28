#include "RotaryEncoder.h"

void RotaryEncoder::setup() {
    pinMode(clk, INPUT_PULLUP);
    pinMode(dt, INPUT_PULLUP);

    const uint8_t msb = digitalRead(clk);
    const uint8_t lsb = digitalRead(dt);
    lastEncoded = (msb << 1) | lsb;

    attachInterruptArg(digitalPinToInterrupt(clk), updateEncoderInterrupt, this, CHANGE);
    attachInterruptArg(digitalPinToInterrupt(dt), updateEncoderInterrupt, this, CHANGE);
}

void RotaryEncoder::loop() {
    int step = 0;

    noInterrupts();

    if (pendingSteps > 0) {
        pendingSteps--;
        step = 1;
    } else if (pendingSteps < 0) {
        pendingSteps++;
        step = -1;
    }

    interrupts();

    if (step == 0) {
        return;
    }

    encoderPos += step;

    if (step > 0) {
        if (onRotationUp != nullptr) {
            onRotationUp();
        }
    } else {
        if (onRotationDown != nullptr) {
            onRotationDown();
        }
    }

    if (onUpdateRotation != nullptr) {
        onUpdateRotation(encoderPos);
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
    auto* encoder = static_cast<RotaryEncoder*>(argument);
    encoder->updateEncoder();
}

void RotaryEncoder::updateEncoder() {

    const uint8_t msb = digitalRead(clk);
    const uint8_t lsb = digitalRead(dt);
    const uint8_t encoded = (msb << 1) | lsb;
    const uint8_t sum = (lastEncoded << 2) | encoded;

    int8_t direction = 0;

    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
        direction = 1;
    }
    else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
        direction = -1;
    }
    else if (encoded != lastEncoded) {
        transitionAccumulator = 0;
    }

    lastEncoded = encoded;

    if (direction == 0) {
        return;
    }

    transitionAccumulator += direction;

    if (transitionAccumulator >= perIndent) {
        transitionAccumulator -= perIndent;
        pendingSteps++;
    } else if (
        transitionAccumulator <= -perIndent
    ) {
        transitionAccumulator += perIndent;
        pendingSteps--;
    }
}
