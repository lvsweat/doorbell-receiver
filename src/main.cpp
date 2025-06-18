#include <Arduino.h>
#include <receiver.hpp>

void on_rf_receive(uint8_t* buf, uint8_t buf_size) {
	// Need to reverse engineer the data that the doorbell transmitter sends out to interpret
	// and create conditionals here. Will do soon.


	const char* msg = "Doorbell rang!"; // Message we want displayed on the desktop
	uint8_t msg_size = sizeof(msg);
	
	uint8_t bytes_to_send[msg_size+2];

	bytes_to_send[0] = 0xAF; // Beginning bytes so the desktop application can verify
	bytes_to_send[1] = 0xBE; // that this serial message is meant for it.

	memcpy(bytes_to_send+0x02, msg, msg_size); // Offest dest by 2 to skip over the beginning bytes
	Serial.write(bytes_to_send, sizeof(bytes_to_send));
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
