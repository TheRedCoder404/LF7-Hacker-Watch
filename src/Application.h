#pragma once

#include <utility>

#include "Components/Display.h"

class Application {
public:
    Application(String name)
        : name(std::move(name)) {}

    void updateDisplay();
    void loop();
    void onScrollUp();
    void onScrollDown();
    void onRotaryButtonPressed();
    void onRotaryButtonReleased();
    void onButtonPressed();
    void onButtonReleased();

    void setUpdateDisplay(void (*callback)(Display& display));
    void setLoop(void (*callback)());
    void setOnScrollUp(void (*callback)());
    void setOnScrollDown(void (*callback)());
    void setOnRotaryButtonPressed(void (*callback)());
    void setOnRotaryButtonReleased(void (*callback)());
    void setOnButtonPressed(void (*callback)());
    void setOnButtonReleased(void (*callback)());

    void setDisplay(Display* display);
    String getName();

private:
    void (*m_updateDisplay)(Display& display) = nullptr;
    void (*m_loop)() = nullptr;
    void (*m_onScrollUp)() = nullptr;
    void (*m_onScrollDown)() = nullptr;
    void (*m_onRotaryButtonPressed)() = nullptr;
    void (*m_onRotaryButtonReleased)() = nullptr;
    void (*m_onButtonPressed)() = nullptr;
    void (*m_onButtonReleased)() = nullptr;

    Display* m_display = nullptr;
    String name;
};
