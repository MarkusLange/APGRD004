#include "lin_bus.h"
#include "apgrd004.h"

// Create an IntervalTimer object
IntervalTimer myTimer;

int ledState = LOW;                // ledState used to set the LED
unsigned long interval = 200000;   // interval at which to blinkLED to run every 0.2 seconds

APGRD004 apgrd004(&Serial1);

#define len 4
uint8_t lin_frame[len];

int lin_cs = 23;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(lin_cs, OUTPUT);
  digitalWrite(lin_cs, HIGH);
  
  Serial.begin(115200);
  Serial.println("APGRD004 Readout Demo");
  
  myTimer.begin(blinkLED, interval);
}

// Keep in mind:
// The response to a status request is four bytes followed by a checksum. The four bytes
// returned are not defined by this version of code.
// also the CRC calculation is not supported so not correct.
void loop() {
  Serial.println(apgrd004.status_request(lin_frame), HEX);
  Serial.println("STATUS REQUEST FRAME");
  frame(lin_frame, 4);
  delay(3000);
}

void frame(uint8_t* data, uint8_t lenght) {
  for (int i=0; i<lenght; i++) {
    if (data[i] < 0x10)
      Serial.print("0");
    
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void blinkLED() {
  ledState = !ledState;
  
  digitalWrite(LED_BUILTIN, ledState);
}