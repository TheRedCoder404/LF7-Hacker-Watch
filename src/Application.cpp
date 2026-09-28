#include "Application.h"

void Application::updateDisplay() {
    if (m_updateDisplay != nullptr && m_display != nullptr) {
        m_updateDisplay(*m_display);
    }
}

void Application::loop() {
    if (m_loop != nullptr) {
        m_loop();
    }
}

void Application::onScrollUp() {
    if (m_onScrollUp != nullptr) {
        m_onScrollUp();
        updateDisplay();
    }
}

void Application::onScrollDown() {
    if (m_onScrollDown != nullptr) {
        m_onScrollDown();
        updateDisplay();
    }
}

void Application::onRotaryButtonPressed() {
    if (m_onRotaryButtonPressed != nullptr) {
        m_onRotaryButtonPressed();
        updateDisplay();
    }
}

void Application::onRotaryButtonReleased() {
    if (m_onRotaryButtonReleased != nullptr) {
        m_onRotaryButtonReleased();
        updateDisplay();
    }
}

void Application::onButtonPressed() {
    if (m_onButtonPressed != nullptr) {
        m_onButtonPressed();
    }
}

void Application::onButtonReleased() {
    if (m_onButtonReleased != nullptr) {
        m_onButtonReleased();
        updateDisplay();
    }
}

void Application::setUpdateDisplay(void (*callback)(Display& display)) {
    m_updateDisplay = callback;
}

void Application::setLoop(void (*callback)()) {
    m_loop = callback;
}

void Application::setOnScrollUp(void (*callback)()) {
    m_onScrollUp = callback;
}

void Application::setOnScrollDown(void (*callback)()) {
    m_onScrollDown = callback;
}

void Application::setOnRotaryButtonPressed(void (*callback)()) {
    m_onRotaryButtonPressed = callback;
}

void Application::setOnRotaryButtonReleased(void (*callback)()) {
    m_onRotaryButtonReleased = callback;
}

void Application::setOnButtonPressed(void (*callback)()) {
    m_onButtonPressed = callback;
}

void Application::setOnButtonReleased(void (*callback)()) {
    m_onButtonReleased = callback;
}

void Application::setDisplay(Display* display) {
    m_display = display;
}

String Application::getName() {
    return name;
}
