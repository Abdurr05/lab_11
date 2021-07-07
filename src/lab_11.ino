
#include "LIS3DH.h"
#include <blynk.h>
SYSTEM_THREAD(ENABLED);

LIS3DHSPI accel(SPI, D3, WKP);

const unsigned long PRINT_SAMPLE_PERIOD = 100;
unsigned long lastPrintSample = 0;

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
  // to get x,y,z from the accelerometer and display it in blynk and in serial
  if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD){
    lastPrintSample = millis();
    if (accel.getSample(sample)){
      Serial.printlnf("%d,%d,%d", sample.x, sample.y, sample.z);
      Blynk.virtualWrite(V0, sample.x);
      Blynk.virtualWrite(V1, sample.y);
      Blynk.virtualWrite(V2, sample.z);
    }
    else{
      Serial.println("no sample");
    }
  }
}
