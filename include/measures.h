#ifndef _mediciones_h_
#define _mediciones_h_

#include <Arduino.h>
#include <Average.h>  //--https://registry.platformio.org/libraries/majenkolibraries/Average/examples/AverageExample/AverageExample.ino
#include "config.h"


//--Macros
#define MAX_SEC_AVE_AN          60                              //register interval in sec
#define MAX_SEC_SAMPLE_AN       1                               //sample interval in sec
#define MAX_mSEC_AVE_AN         ((MAX_SEC_AVE_AN)*(1000))       //register interval in msec
#define MAX_mSEC_SAMPLE_AN      ((MAX_SEC_SAMPLE_AN)*(1000))    //sample interval in msec

#define DEBUG_MEAS //for debug purposes

//--Sensors pins
#define TEMP_AMB_PIN            39
#define TEMP_EXT_PIN            36

//--Enumeration for sensors
enum sensor_type{
    TC1047=0,
    LM35,
    DHT22,
    DHT11,
    LOOP420mA
};

//--Enumeration for types of variables
enum var_type{
    ANALOGVAR=0,
    DIGITALVAR
};

//--Enumeration for variable position in data structure
enum var_pos{
    TEMP_AMB=0,
    TEMP_EXT
};

//--Structures for measured variables
struct Data {
  const char* name;
  uint16_t raw_value;
  float inst_value;
  float ave_value;
  float sd_value;
  float max_value;
  float min_value;
  uint8_t sensor;
  uint8_t type;
  uint8_t pin;
};

struct Process {
    Average<float> pr();
    //Average<float> pr(600);
};


//--Public prototypes
void measure_init(void);
uint8_t measure_count(void);
Data * measure_loop(void);

//--Private prototypes
void measure_read_sensor(void);
float measure_unit_calc(uint8_t reg_idx, uint16_t unit);




#endif