#pragma once

#include "AppSelector.h"
#include "HandshakeGrabberApp.h"
#include "SettingsApp.h"
#include "SystemAccessApp.h"
#include "WifiCrackApp.h"
#include "riddles/BinaryRiddleApp.h"
#include "riddles/CodeRiddleApp.h"
#include "riddles/LogicRiddleApp.h"
#include "riddles/OSIRiddleApp.h"

class Apps {
public:
    static AppSelector& getAppSelector();
    static WifiCrackApp& getWifiCrack();
    static HandshakeGrabberApp& getHandshakeGrabber();
    static SettingsApp& getSettings();
    static OSIRiddleApp& getOSIRiddle();
    static BinaryRiddleApp& getBinaryRiddle();
    static LogicRiddleApp& getLogicRiddle();
    static CodeRiddleApp& getCodeRiddle();

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
    static BinaryRiddleApp binaryRiddle;
    static LogicRiddleApp logicRiddle;
    static CodeRiddleApp codeRiddle;

    static Application *apps[];
    static Application *handshakeApps[];
};
