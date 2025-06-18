#include <Arduino.h>
#include <receiver.hpp>

void on_rf_receive(uint8_t* buf, uint8_t buf_size) {
	// Need to reverse engineer the signals that the doorbell transmitter sends out to interpret
	// and create conditional here. Will do soon.
}

rf_receiver* rcvr;

void setup() {
	Serial.begin(115200); // Begin serial comms
	rcvr = new rf_receiver(2000, 4); // Create/allocate new receiver object on heap
	rcvr->set_on_receive(on_rf_receive); // Override existing empty callback with our callback
}

void loop() {
	rcvr->recv();   // Constantly check for valid communications received. Will call on_rf_receive
				    // when internal checksum pass in the wrapped driver receive function
}
