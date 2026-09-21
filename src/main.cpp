#include "main.h"

#include <Arduino.h>

#include "LiquidCrystal.h"
#include "Encoder.h"

constexpr int rs = D5, en = D6, d4 = D0, d5 = D1, d6 = D2, d7 = D3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const uint8_t rotarySw = D10;
const uint8_t rotaryDt = D9;
const uint8_t rotaryClk = D8;
static Encoder encoder(rotaryDt, rotaryClk);

long rotaryState = -999;
bool pressed = false;
volatile bool toBePressed = false;

void setup() {
    pinMode(rotarySw, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(rotarySw), onRotarySwitch, FALLING);

    lcd.begin(16, 2);
    lcd.print("Hello World");
    lcd.setCursor(12, 0);
    lcd.print("fals");
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
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hello World");
    lcd.setCursor(12, 0);
    lcd.print(pressed ? "fals" : "true");
    lcd.setCursor(0, 1);
    lcd.print("rota: ");
    lcd.print(rotaryState);
}
