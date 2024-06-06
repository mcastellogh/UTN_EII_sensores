#ifndef _config_h_
#define _config_h_

//--Includes
#include <Arduino.h>

//--Hardware PINS definitions
#define ONBOARD_LED_PIN             2
#define LED_PIN                     23



//--Software constants
#define SERIAL_BAUDRATE             19200


//--Structures
struct Config {
  float offset;
  float gain;
  uint8_t sensor;
};

//--Prototypes
void App_setup(void);
void App_loop(void);


#endif