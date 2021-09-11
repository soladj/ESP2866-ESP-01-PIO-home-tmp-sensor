#include <EEPROM.h>

#define EEPROM_TEMPERATURE_SEL_DIR 0
#define EEPROM_CALEFACTOR_POWER_DIR 1

#define TEMPERATURE_SEL_DEFAULT 2000
#define TEMPERATURE_SEL_MAX 3500
#define TEMPERATURE_SEL_MIN 1000
#define CALEFACTOR_POWER_DEFAULT 1
#define CALEFACTOR_POWER_MAX 1
#define CALEFACTOR_POWER_MIN 0

void eeprom_init(int n_var) {
    EEPROM.begin(sizeof(uint16_t)*n_var);
}

uint16_t read_memory(int dir)
{
  uint16_t value;
  value = EEPROM.read(dir*2)&0xFF;
  value <<= 8;
  value |= EEPROM.read(dir*2+1)&0xFF;
  return value;
}


void update_memory(int dir, uint16_t value)
{
  if (read_memory(dir) != value) {
    uint16_t value_tmp = value;
    EEPROM.write(dir*2, (uint8_t) (value_tmp>>8)&0xFF);
    EEPROM.write(dir*2+1, (uint8_t) value_tmp&0xFF);
    EEPROM.commit();
  }
}

uint16_t read_eeprom_temperature_sel(void) {
  uint16_t value = read_memory(EEPROM_TEMPERATURE_SEL_DIR);
  if(value==0xFFFF)
  {
    value = TEMPERATURE_SEL_DEFAULT;
  }
  return value;
}

uint16_t update_eeprom_temperature_sel(uint16_t value) {
  uint16_t val =  value;
  if (val>TEMPERATURE_SEL_MAX) 
  {
    val = TEMPERATURE_SEL_MAX;
  } 
  else if (val<TEMPERATURE_SEL_MIN) 
  {
    val = TEMPERATURE_SEL_MIN;
  }
  update_memory(EEPROM_TEMPERATURE_SEL_DIR, val);
  return val;
}
