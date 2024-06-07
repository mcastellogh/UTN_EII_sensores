//=======================================================================
// File:                setup.cpp
// Author:              Marcelo Castello (https://github.com/mcastellogh)
// Licence:             GPLV3+
// Version:             1.0.0
// Date:                Mayo 2024
// Info:                Project for Electrónica II
//=======================================================================

//--Includes
#include "setup.h"

//--Harcoded local variables
const char * device_name="device01";
const char * device_type="Sensor";

//--Local variables
uint8_t var_count;

//--Startup function
void App_setup(void){
    Serial.begin(SERIAL_BAUDRATE);

    //--PINS
    pinMode(ONBOARD_LED_PIN,OUTPUT);
    pinMode(ACT_LED_PIN,OUTPUT);

    //--Init measures
    measure_init();

    //--Calculate the number of variables in Data Structure
    var_count=measure_count();

    led_welcome();

    //--Presentation
    Serial.print("Cátedra de Electrónica II UTN-FRRO");
    Serial.println("Utilización de sensores analógicos y digitales");
}