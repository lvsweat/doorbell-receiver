#pragma once

#include <Arduino.h>
#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif

typedef std::function<void(uint8_t* buffer, uint8_t buffer_size)> OnReceiveCallback;

struct rf_receiver {
public:
    rf_receiver(uint16_t speed, uint8_t rxPin);
    ~rf_receiver();
    bool initialize();
    void recv();
    void set_on_receive(OnReceiveCallback on_receive_callback);
private:
    RH_ASK* p_rf_driver = nullptr;
    OnReceiveCallback* p_on_receive = nullptr;
};