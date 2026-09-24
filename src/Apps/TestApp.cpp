#include "TestApp.h"

int TestApp::scroll = 0;
bool TestApp::pressed = false;

void TestApp::setup() {
    m_app.setUpdateDisplay(&onUpdateDisplay);
    m_app.setOnScrollUp(&onScrollUp);
    m_app.setOnScrollDown(&onScrollDown);
    m_app.setOnRotaryButtonPressed(&onRotaryButtonPressed);
}

Application& TestApp::getApp() {
    return m_app;
}

void TestApp::onUpdateDisplay(Display& display) {
    display.clear();
    display.setCursor(0, 0);
    display.print("Hello World");
    display.setCursor(12, 0);
    display.print(pressed ? "fals" : "true");
    display.setCursor(0, 1);
    display.print("scroll: ");
    display.print(scroll);
}

void TestApp::onScrollUp() {
    scroll++;
}

void TestApp::onScrollDown() {
    scroll--;
}

void TestApp::onRotaryButtonPressed() {
    pressed = !pressed;
}


