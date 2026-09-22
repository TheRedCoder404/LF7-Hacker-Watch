#include "TestApp.h"

void TestApp::setup() {
    m_app.setUpdateDisplay(&updateDisplay);
}

Application& TestApp::getApp() {
    return m_app;
}

void TestApp::updateDisplay() {
    
}


