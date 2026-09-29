#include "AppSelector.h"

#include "Apps.h"
#include "Utility.h"
#include "WindowManager.h"

const String AppSelector::SELECTED_SYMBOL = "[x]";
const String AppSelector::NOT_SELECTED_SYMBOL = "[ ]";

int AppSelector::scroll = 0;
int AppSelector::viewScroll = 0;
bool AppSelector::pressed = false;

void AppSelector::setUp() {
    app.setUpdateDisplay(&onUpdateDisplay);
    app.setOnScrollUp(&onScrollUp);
    app.setOnScrollDown(&onScrollDown);
    app.setOnRotaryButtonPressed(&onRotaryButtonPressed);
}

Application& AppSelector::getApp() {
    return app;
}

void AppSelector::onUpdateDisplay(Display &display) {
    display.clear();

    if (viewScroll < Apps::getAppCount()) {
        display.setCursor(0, 0);
        display.print(getAppNameAt(viewScroll));
    }

    if (viewScroll + 1 < Apps::getAppCount()) {
        display.setCursor(0, 1);
        display.print(getAppNameAt(viewScroll + 1));
    }
}

String AppSelector::getAppNameAt(int index) {
    if (index < 0 || index >= Apps::getAppCount()) {
        return "";
    }

    const String selected = index == scroll ? SELECTED_SYMBOL : NOT_SELECTED_SYMBOL;
    return selected + Apps::getApps()[index]->getName();
}

void AppSelector::onScrollUp() {
    scroll--;
    Utility::clamp(scroll, 0, Apps::getAppCount() - 1);

    if (scroll < viewScroll) {
        scrollViewUp();
    }
}

void AppSelector::onScrollDown() {
    scroll++;
    Utility::clamp(scroll, 0, Apps::getAppCount() - 1);

    if (scroll > viewScroll + 1) {
        scrollViewDown();
    }
}

void AppSelector::scrollViewUp() {
    viewScroll--;
}

void AppSelector::scrollViewDown() {
    viewScroll++;
}

void AppSelector::onRotaryButtonPressed() {
    Application* selectedApp = Apps::getApps()[scroll];
    if (selectedApp != nullptr) {
        WindowManager::setCurrentApp(*selectedApp);
        selectedApp->onSelected();
    }
}


