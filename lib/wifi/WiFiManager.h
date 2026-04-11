#pragma once

#include "NVS.h"
#include "Network.h"
#include "Driver.h"

class WifiManager {
public:
    WifiManager();
    void start();

private:
    NVS nvs;
    Network network;
    Driver driver;
    void init();
};