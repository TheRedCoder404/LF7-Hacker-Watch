#include "Apps.h"

AppSelector Apps::appSelector = AppSelector();
WifiCrackApp Apps::wifiCrack = WifiCrackApp();
HandshakeGrabberApp Apps::handshakeGrabber = HandshakeGrabberApp();
SystemAccessApp Apps::systemAccess = SystemAccessApp();
SettingsApp Apps::settings = SettingsApp();
Application *Apps::apps[] = {&wifiCrack.getApp(), &handshakeGrabber.getApp(), &systemAccess.getApp(), &settings.getApp()};

AppSelector& Apps::getAppSelector() {
    return appSelector;
}

WifiCrackApp & Apps::getWifiCrack() {
    return wifiCrack;
}

HandshakeGrabberApp & Apps::getHandshakeGrabber() {
    return handshakeGrabber;
}

SettingsApp & Apps::getSettings() {
    return settings;
}

Application **Apps::getApps() {
    return apps;
}

int Apps::getAppCount() {
    return sizeof(apps) / sizeof(Application *);
}
