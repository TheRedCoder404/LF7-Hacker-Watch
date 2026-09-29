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
    scroll--;
    Utility::clamp(scroll, 0, optionsSize - 1);

    if (scroll < viewScroll) {
        scrollViewUp();
    }
}

void Selector::onScrollDown() {
    scroll++;
    Utility::clamp(scroll, 0, optionsSize - 1);

    if (scroll > viewScroll + 1) {
        scrollViewDown();
    }
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

    String selected = "";
    if (selectable) {
        selected = index == scroll ? selectedSymbol : notSelectedSymbol;
    }
    return selected + optionLabels[index];
}
