#include <Arduino.h>
#include <receiver.hpp>

void on_rf_receive(uint8_t* buf, uint8_t buf_size) {

}

rf_receiver* rcvr;

void setup() {
	Serial.begin(115200);
	rcvr = new rf_receiver(2000, 4);
	rcvr->set_on_receive(on_rf_receive);
}

void loop() {
	rcvr->recv();
}
