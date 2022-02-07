#include "lin_bus.h"
#include "apgrd004.h"

// Create an IntervalTimer object
IntervalTimer myTimer;

int ledState = LOW;                // ledState used to set the LED
unsigned long interval = 200000;   // interval at which to blinkLED to run every 0.2 seconds

APGRD004 apgrd004(&Serial1);

int lin_cs = 23;

//                  R    G    B
uint8_t rgb_r[3] = {255,   0,   0};
uint8_t rgb_g[3] = {  0, 255,   0};
uint8_t rgb_b[3] = {  0,   0, 255};
int intensity = 0x1F;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(lin_cs, OUTPUT);
  digitalWrite(lin_cs, HIGH);
  
  Serial.begin(115200);
  Serial.println("APGRD004 Fade Demo");
  
  myTimer.begin(blinkLED, interval);
}

void loop() {
  Serial.println("intensity ramp up");
  float rampup_delay = 4;
  apgrd004.set_ramp_up(intensity, rgb_r);
  delay((int)rampup_delay*1000);
  
  Serial.println("intensity dim down");
  float dimdown_delay = 4;
  apgrd004.set_dim_down(intensity, rgb_g);
  delay((int)dimdown_delay*1000);
}

void blinkLED() {
  ledState = !ledState;
  
  digitalWrite(LED_BUILTIN, ledState);
}