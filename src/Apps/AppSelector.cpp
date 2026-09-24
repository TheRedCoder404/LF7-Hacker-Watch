#include "AppSelector.h"

#include "Apps.h"
#include "Utility.h"

const String AppSelector::SELECTED_SYMBOL = "[x]";
const String AppSelector::NOT_SELECTED_SYMBOL = "[ ]";

int AppSelector::scroll = 0;
int AppSelector::viewScroll = 0;
bool AppSelector::pressed = false;

void AppSelector::setUp() {
    app.setUpdateDisplay(&onUpdateDisplay);
    app.setOnScrollUp(&onScrollUp);
    app.setOnScrollDown(&onScrollDown);
}

Application & AppSelector::getApp() {
    return app;
}

void AppSelector::onUpdateDisplay(Display &display) {
    display.clear();

    if (scroll <= Apps::getAppCount()) {
        display.setCursor(0, 0);
        display.print(getAppNameAt(scroll));
    }

    if (scroll + 1 <= Apps::getAppCount()) {
        display.setCursor(0, 1);
        display.print(getAppNameAt(scroll + 1));
    }
}

String AppSelector::getAppNameAt(int index) {
    const String selected = index == scroll ? SELECTED_SYMBOL : NOT_SELECTED_SYMBOL;
    return selected + Apps::getApps()[index]->getName();
}

void AppSelector::onScrollUp() {
    scroll--;
    Utility::clamp(scroll, 0, Apps::getAppCount() - 1);
}

void AppSelector::onScrollDown() {
    scroll++;
    Utility::clamp(scroll, 0, Apps::getAppCount() - 1);
}

void AppSelector::onRotaryButtonPressed() {

}


