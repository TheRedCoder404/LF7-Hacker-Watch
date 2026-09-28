#pragma once

#include <WString.h>

#include "Application.h"

class Selector {
public:
    template <size_t N>
    Selector(const String (&options)[N])
        : optionsSize(N)
        , optionLabels(options) {}

    int getCurrentSelected();
    void onUpdateDisplay(Display& display);
    void onScrollUp();
    void onScrollDown();

private:
    const String selectedSymbol = "[X]";
    const String notSelectedSymbol = "[ ]";

    int scroll = 0;
    int viewScroll = 0;
    int optionsSize;

    const String* optionLabels;

    void scrollViewUp();
    void scrollViewDown();
    String getFullOptionAt(int index);
};
