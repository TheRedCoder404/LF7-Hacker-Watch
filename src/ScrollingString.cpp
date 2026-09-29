#include "ScrollingString.h"

#include "Arduino.h"
#include "WindowManager.h"

void ScrollingString::loop() {
    const long mills = millis();
    if (scrollPos == 0) {
        if (mills - lastTiming < scrollDoneDelay) {
            return;
        }

        lastTiming = mills;
        scrollPos++;
        WindowManager::updateDisplay();
        return;
    }

    if (scrollPos < maxScrollPos) {
        if (mills - lastTiming < scrollDelay) {
            return;
        }

        lastTiming = mills;
        scrollPos++;
        WindowManager::updateDisplay();
        return;
    }

    if (mills - lastTiming >= scrollDoneDelay) {
        lastTiming = mills;
        scrollPos = 0;
        WindowManager::updateDisplay();
    }
}

void ScrollingString::reset() {
    scrollPos = 0;
    lastTiming = millis();
}

String ScrollingString::getTextSlice() {
    return scrollText.substring(scrollPos, 16 + scrollPos);
}

void ScrollingString::setText(const String &text) {
    scrollText = text;
    maxScrollPos = scrollText.length() - 16;
    reset();
}
