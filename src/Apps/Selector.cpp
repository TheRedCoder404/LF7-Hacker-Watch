#include "Selector.h"

#include "Utility.h"


int Selector::getCurrentSelected() {
    return scroll;
}

void Selector::onUpdateDisplay(Display &display) {
    display.clear();

    if (viewScroll < optionsSize) {
        display.setCursor(0, 0);
        display.print(getFullOptionAt(viewScroll));
    }

    if (viewScroll + 1 < optionsSize) {
        display.setCursor(0, 1);
        display.print(getFullOptionAt(viewScroll + 1));
    }
}

void Selector::onScrollUp() {
    if (scroll < viewScroll) {
        scrollViewUp();
    }

    scroll--;
    Utility::clamp(scroll, 0, 1);
}

void Selector::onScrollDown() {
    if (scroll > viewScroll + 1) {
        scrollViewDown();
    }

    scroll++;
    Utility::clamp(scroll, 0, 1);
}

void Selector::scrollViewUp() {
    viewScroll--;
}

void Selector::scrollViewDown() {
    viewScroll++;
}

String Selector::getFullOptionAt(int index) {
    if (index < 0 || index >= optionsSize) {
        return "";
    }

    const String selected = index == scroll ? selectedSymbol : notSelectedSymbol;
    return selected + optionLabels[index];
}
