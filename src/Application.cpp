#include "Application.h"

void Application::updateDisplay() {
    m_updateDisplay();
}

void Application::setUpdateDisplay(void (*callback)()) {
    m_updateDisplay = callback;
}
