//=======================================================================
// File:                setup.cpp
// Author:              Marcelo Castello (https://github.com/mcastellogh)
// Licence:             GPLV3+
// Version:             1.0.0
// Date:                Mayo 2024
// Info:                Proyect template for Electrónica II
//=======================================================================

#include "setup.h"

//--Harcoded local variables
const char * device_name="device01";
const char * device_type="LedDriver";

uint8_t var_count;

void App_setup(void){
    Serial.begin(SERIAL_BAUDRATE);

    //--PINS
    pinMode(ONBOARD_LED_PIN,OUTPUT);
    pinMode(LED_PIN,OUTPUT);

    //--Init measures
    measure_init();

    //--Calculate the number of variables in Data Structure
    var_count=measure_count();

    welcome();

    //--Presentation
    Serial.printf("\r\nCátedra de Electrónica II UTN-FRRO\r\n");
}