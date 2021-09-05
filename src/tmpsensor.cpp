#include <Arduino.h>

#define CALEFACTOR_TEMPERATURE_MARGIN 50

void setup_tmpsensor()
{
}

bool loop_tmpsensor(uint16_t* temperature, uint16_t* t_sel, uint16_t* c_status, uint8_t zone) {
  bool ret = false;
  // Serial.print("C_STATUS <: ");
  // Serial.println(~(*c_status)&DEVICE_ZONE);
  if (*temperature < (*t_sel-CALEFACTOR_TEMPERATURE_MARGIN) && ~(*c_status)&(1<<zone)) {
    *c_status |= 1<<zone;
    ret = true;
  } else {
    // Serial.print("C_STATUS >: ");
    // Serial.println(*c_status&DEVICE_ZONE);
    if (*temperature > (*t_sel+CALEFACTOR_TEMPERATURE_MARGIN) && (*c_status&(1<<zone))) {
      *c_status &= ~(1<<zone);
      ret = true;
    }
    delay(1000);
  }
  return ret;
}
