#include "Display.h"

void Display::print(String text) {
    m_lcd.print(text);
}

void Display::print(long num) {
    m_lcd.print(num);
}

void Display::setCursor(uint8_t x, uint8_t y) {
    m_lcd.setCursor(x, y);
}

void Display::clear() {
    m_lcd.clear();
}
