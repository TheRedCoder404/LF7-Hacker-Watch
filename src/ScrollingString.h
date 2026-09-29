#pragma once

#include <WString.h>

class ScrollingString {
public:
    ScrollingString(const String& text, const int delay, const int doneDelay)
        : scrollText(text)
        , maxScrollPos(text.length() - 16)
        , scrollDelay(delay)
        , scrollDoneDelay(doneDelay) {}

    void loop();
    void reset();
    String getTextSlice();
    void setText(const String& text);

private:
    String scrollText;
    int scrollPos = 0;
    long lastTiming = 0;
    int maxScrollPos;
    const int scrollDelay;
    const int scrollDoneDelay;
};
