#include <Arduino.h>
#include "apgrd004.h"
#include "lin_bus.h"

typedef struct {
  // ZONE<3:0>: Zone Select
  // 0000 = No zones
  // 0001 = Zone 1
  // 0010 = Zone 2
  // 0011 = Zone 1 and 2
  // 0100 = Zone 3
  // 0101 = Zone 1 and 3
  // 0110 = Zone 2 and 3
  // 0111 = Zone 1, 2 and 3
  // 1000 = Zone 4
  // 1001 = Zone 4 and 1
  // 1010 = Zone 4 ad 2
  // 1011 = Zone 4, 1 and 2
  // 1100 = Zone 4 and 3
  // 1101 = Zone 4, 1 and 3
  // 1110 = Zone 4, 2 and 3
  // 1111 = All zones
  uint8_t zones = 0x0F;
  // DIMDWN: Dim Down to Zero From Intensity Selected by bits<4:0>
  // 1 = Dim out
  // 0 = No dim
  uint8_t DIMDWN = 0;
  // RAMPUP: Ramp Up From Zero to Intensity Selected by bits<4:0>
  // 1 = Ramp up
  // 0 = No ramp
  uint8_t RAMPUP = 0;
} basic_settings;

basic_settings setting;

// LED1 = 0, LED2 = 1, LED2 = 2
#define led_r 0
#define led_g 1
#define led_b 2

#define AmbientLightID       0x23
#define AmbientLightStatusID 0x24

#define len 5
uint8_t lin_data[len];

APGRD004::APGRD004(HardwareSerial* stream, uint16_t baudrate) : LIN(stream, baudrate) {
  //
}

void APGRD004::command(uint8_t intensity, uint8_t ramp_up, uint8_t dim_down, uint8_t* color, uint8_t zones) {
  lin_data[0] = 0x00 | ((dim_down & 0x01) << 7) | ((ramp_up & 0x01) << 6) | (intensity & 0x1F);
  lin_data[1] = 0x00 | color[led_r];
  lin_data[2] = 0x00 | color[led_g];
  lin_data[3] = 0x00 | color[led_b];
  lin_data[4] = 0x00 | (zones & 0x0F);
  
  LIN::order(AmbientLightID, lin_data, 5);
}

int APGRD004::status_request(uint8_t* recv_data) {
  return LIN::response(AmbientLightStatusID, recv_data, 4);
}

void APGRD004::set_zones(uint8_t node){
  setting.zones = node;
}

void APGRD004::set_color(uint8_t intensity, uint8_t* color) {
  command(intensity, setting.RAMPUP, setting.DIMDWN, color, setting.zones);
}

void APGRD004::set_dim_down(uint8_t intensity, uint8_t* color) {
  command(intensity, setting.RAMPUP, 1, color, setting.zones);
}

void APGRD004::set_ramp_up(uint8_t intensity, uint8_t* color) {
  command(intensity, 1, setting.DIMDWN, color, setting.zones);
}