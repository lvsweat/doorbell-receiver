#include "receiver.hpp"

rf_receiver::rf_receiver(uint16_t speed, uint8_t rxPin)
{
    p_rf_driver = new RH_ASK(speed, rxPin, 5, 0);
    p_on_receive = new OnReceiveCallback([](uint8_t*, uint8_t){}); // Initialize callback with empty function

    if(!initialize()) {
        Serial.println("Total driver initialization failure. Please check connections and restart.");
    }
}

rf_receiver::~rf_receiver()
{
    // Deallocate heap allocations
    delete(p_rf_driver);
    delete(p_on_receive);
}

bool rf_receiver::initialize()
{
    int retry_count = 0;
    bool initialized = false;
    while (!initialized && retry_count < 5) { // RF ASK driver initialization attempt. Will try 5 times.
        initialized = p_rf_driver->init();
        if (!initialized) {
            Serial.println("Failed RF driver initilization. Trying again now.");
            delay(1000);
            ++retry_count;
        }
    }
}

void rf_receiver::recv() {
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN]; // Allocate byte array buffer with max possible size
    uint8_t bufLen = sizeof(buf);

    if (p_rf_driver->recv(buf, &bufLen)) { // Will be true when an internal checksum passes on the received data.
        p_rf_driver->printBuffer("Buffer received: ", buf, bufLen);
        p_on_receive->operator()(buf, bufLen); // Call callback function
    }
}

void rf_receiver::set_on_receive(OnReceiveCallback onReceiveCallback) {
    p_on_receive = new OnReceiveCallback(onReceiveCallback); // Allocate copy of passed callback function on heap
}