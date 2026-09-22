#include "main.h"

#include <Arduino.h>

#include "Display.h"
#include "Encoder.h"

const uint8_t rotarySw = D10;
const uint8_t rotaryDt = D9;
const uint8_t rotaryClk = D8;
static Encoder encoder(rotaryDt, rotaryClk);

long rotaryState = -999;
bool pressed = false;
volatile bool toBePressed = false;

static Display display;

void setup() {
    display = Display();

    pinMode(rotarySw, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(rotarySw), onRotarySwitch, FALLING);

    display.print("Hello World");
    display.setCursor(12, 0);
    display.print("fals");
}

void loop() {
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
    display.setCursor(0, 1);
    display.print("rota: ");
    display.print(rotaryState);
}
