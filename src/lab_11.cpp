/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Abdurrahman/Documents/labs/lab_11/src/lab_11.ino"

#include "LIS3DH.h"
#include <blynk.h>
void setup();
void loop();
#line 4 "c:/Users/Abdurrahman/Documents/labs/lab_11/src/lab_11.ino"
const unsigned long PRINT_SAMPLE_PERIOD = 100;

unsigned long lastPrintSample = 0;


// Example using position detection feature of the LIS3DH and SPI connection, like the AssetTracker
SYSTEM_THREAD(ENABLED);

// LIS3DH is connected as in the AssetTracker, to the primary SPI with A2 as the CS (SS) pin, and INT connected to WKP
LIS3DHSPI accel(SPI, D3, WKP);



void setup() {
	Serial.begin(9600);
  Blynk.begin("2CWaNQmhBm6ocgYr7F0AVxtpOOQpAaSl", IPAddress(167, 172, 234, 162), 9090);

	delay(5000);

	// Initialize sensors
	LIS3DHConfig config;
	config.setPositionInterrupt(16);

	bool setupSuccess = accel.setup(config);
	Serial.printlnf("setupSuccess=%d", setupSuccess);
}

void loop() {
	LIS3DHSample sample;
  Blynk.run();

		if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD) {
		lastPrintSample = millis();
		if (accel.getSample(sample)) {
			Serial.printlnf("%d,%d,%d", sample.x, sample.y, sample.z);
      Blynk.virtualWrite(V0, sample.x);
      Blynk.virtualWrite(V1, sample.y);
      Blynk.virtualWrite(V2, sample.z);
		}
		else {
			Serial.println("no sample");
		}
    }
		
}
