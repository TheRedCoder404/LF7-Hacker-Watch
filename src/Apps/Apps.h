#pragma once

#include "AppSelector.h"
#include "HandshakeGrabberApp.h"
#include "SettingsApp.h"
#include "SystemAccessApp.h"
#include "WifiCrackApp.h"

class Apps {
public:
    static AppSelector& getAppSelector();
    static WifiCrackApp& getWifiCrack();
    static HandshakeGrabberApp& getHandshakeGrabber();
    static SettingsApp& getSettings();
    static OSIRiddleApp& getOSIRiddle();

    static Application **getApps();
    static Application **getHandshakeApps();
    static int getAppCount();

private:
    static AppSelector appSelector;
    static WifiCrackApp wifiCrack;
    static HandshakeGrabberApp handshakeGrabber;
    static SystemAccessApp systemAccess;
    static SettingsApp settings;
    static OSIRiddleApp osiRiddle;

    static Application *apps[];
    static Application *handshakeApps[];
};
