#pragma once

#include <pins_arduino.h>
#include <WString.h>

#include "LiquidCrystal.h"

class Display {
public:
    Display()
        : m_lcd(m_rs, m_en, m_d4, m_d5, m_d6, m_d7) {
        m_lcd.begin(m_displayWidth, m_displayHeight);
    }

    void print(String text);
    void print(long num);
    void setCursor(uint8_t x, uint8_t y);
    void clear();

private:
    static constexpr int m_rs = D5, m_en = D6, m_d4 = D0, m_d5 = D1, m_d6 = D2, m_d7 = D3;
    static constexpr int m_displayWidth = 16, m_displayHeight = 2;
    LiquidCrystal m_lcd;
};
