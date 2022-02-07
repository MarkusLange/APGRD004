#include <Arduino.h>
#include "lin_bus.h"

class APGRD004 : public LIN {

private:
  void command(uint8_t intensity, uint8_t ramp_up, uint8_t dim_down, uint8_t* color, uint8_t zones);
  
public:
  static const int BIT_RATE = 19200;
  APGRD004(HardwareSerial* stream, uint16_t baudrate = BIT_RATE);
  int status_request(uint8_t* recv_data);
  void set_zones(uint8_t node);
  void set_color(uint8_t intensity, uint8_t* color);
  void set_dim_down(uint8_t intensity, uint8_t* color);
  void set_ramp_up(uint8_t intensity, uint8_t* color);
};