#pragma once

class Network {
    private:
       void setNetworkStack();
       void setEventLoop();
       void setHotSpot();

    public:
        void init();
};