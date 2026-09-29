#include "Apps.h"

#include "riddles/BinaryRiddleApp.h"

AppSelector Apps::appSelector = AppSelector();
WifiCrackApp Apps::wifiCrack = WifiCrackApp();
HandshakeGrabberApp Apps::handshakeGrabber = HandshakeGrabberApp();
SystemAccessApp Apps::systemAccess = SystemAccessApp();
SettingsApp Apps::settings = SettingsApp();
OSIRiddleApp Apps::osiRiddle = OSIRiddleApp();
BinaryRiddleApp Apps::binaryRiddle = BinaryRiddleApp();
Application *Apps::apps[] = {&wifiCrack.getApp(), &handshakeGrabber.getApp(), &systemAccess.getApp(), &settings.getApp()};
Application *Apps::handshakeApps[] = {&osiRiddle.getApp(), &binaryRiddle.getApp()};

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

OSIRiddleApp & Apps::getOSIRiddle() {
    return osiRiddle;
}

BinaryRiddleApp & Apps::getBinaryRiddle() {
    return binaryRiddle;
}

Application **Apps::getApps() {
    return apps;
}

Application ** Apps::getHandshakeApps() {
    return handshakeApps;
}

int Apps::getAppCount() {
    return sizeof(apps) / sizeof(Application *);
}
