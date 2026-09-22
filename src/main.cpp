#include "main.h"

#include <Arduino.h>

#include "Program.h"

Program *program;

void setup() {
    program = new Program();

    onDisplayChange();
}

void loop() {
    program->loop();

    if (toBePressed) {
        static uint32_t lastPressTime = 0;
        uint32_t now = millis();

        if (now - lastPressTime >= 50) {
            lastPressTime = now;
            pressed = !pressed;
            toBePressed = false;

            onDisplayChange();
        }
    }

    long current = encoder.read();
    if (current == rotaryState) {
        return;
    }

    rotaryState = current;
    onDisplayChange();
}

void IRAM_ATTR onRotarySwitch() {
    toBePressed = true;
}

void onDisplayChange() {
    display.clear();
    display.setCursor(0, 0);
    display.print("Hello World");
    display.setCursor(12, 0);
    display.print(pressed ? "fals" : "true");
}
