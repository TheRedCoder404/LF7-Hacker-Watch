#pragma once

class Application {
public:
    void updateDisplay();
    void setUpdateDisplay(void (*callback)());

private:
    static void (*m_updateDisplay)();
};
