//=======================================================================
// File:                measures.cpp
// Author:              Marcelo Castello (https://github.com/mcastellogh)
// Licence:             GPLV3+
// Version:             1.0.0
// Date:                Mayo 2024
// Info:                Measures external sensors
//=======================================================================

//--Includes
#include "measures.h"

//--Local variables
float lm35gain=1;
float lm35offset=0;
float tc1047gain=1;
float tc1047offset=0;
uint32_t msec_an_reg;
uint32_t msec_an_sample;
uint8_t sample=0;

//--Extern variables
extern Config config;


//--Create data array with variables to measure
//-- Each variable is called 'register'
//--Example:
//  "Humedad", 0, 0, 0, 0, RH, DIGITALVAR, DHT22_PIN 
Data data[] = {
    // name, raw_value, inst_value, ave_value, sd_value, max_value, min_value, sensor, type, pin
    "Temperatura ambiente", TEMP_AMB, 0, 0, 0, 0, 0, 0, TC1047, ANALOGVAR, TEMP_AMB_PIN,0,
    "Temperatura exterior", TEMP_EXT, 0, 0, 0, 0, 0, 0, TC1047, ANALOGVAR, TEMP_EXT_PIN,0
};

const char* name;
uint8_t variable;
uint16_t raw_value;
float inst_value;
float ave_value;
float sd_value;
float max_value;
float min_value;
uint8_t sensor;
uint8_t type;
uint8_t pin;
bool procesed;

//--Calculate number of variables in Data Structure
const uint8_t numberOfVars = sizeof(data) / sizeof(data[0]);

//--Create array_proc objet to calculate average, max, min & sd for variable readings
Average<float>* array_proc[numberOfVars];


//-----------------------------------------------------------------------------
//--Public functions-----------------------------------------------------------
//-----------------------------------------------------------------------------


void measure_init(void){
    //uint16_t samples=config.t_reg/config.t_sample; //for future features
    uint16_t samples=MAX_mSEC_AVE_AN/MAX_mSEC_SAMPLE_AN; //Calculate number of samples based on register time (average time) and sample time
    msec_an_reg=millis();
    msec_an_sample=millis();
    Serial.println(numberOfVars);
    //--Build a process array for each variable
    //--This array is used for Average library to calculate min, max, mean & sd values for each variable
    for (int i = 0; i < numberOfVars; i++) {
        array_proc[i] = new Average<float>(samples);
    }
}

uint8_t measure_count(void){
    return numberOfVars;
}

Data * measure_loop(void){
    if((millis()-msec_an_sample)>=MAX_mSEC_SAMPLE_AN){
        #ifdef DEBUG_MEAS
            Serial.print("[DEBUG] Take a sample:");
            sample++;
            Serial.println(sample);
        #endif
        led_flash(20, 1, ACT_LED_PIN);
        _measure_read_sensor();
        msec_an_sample=millis();
    }
    if((millis()-msec_an_reg)>=MAX_mSEC_AVE_AN){
        #ifdef DEBUG_MEAS
            Serial.println("[DEBUG] Process...");
            sample=0;
        #endif
        for (uint8_t var_idx=0;var_idx<numberOfVars;var_idx++){
            if(data[var_idx].type==ANALOGVAR){
                data[var_idx].ave_value=array_proc[var_idx]->mean();
                data[var_idx].ave_value=array_proc[var_idx]->mean();
                data[var_idx].sd_value=array_proc[var_idx]->stddev();
                data[var_idx].max_value=array_proc[var_idx]->maximum();
                data[var_idx].min_value=array_proc[var_idx]->minimum();        
                data[var_idx].procesed=true;
                msec_an_reg=millis();
                led_flash(25, 5, ACT_LED_PIN);
                #ifdef DEBUG_MEAS
                    Serial.printf("[DEBUG] %s: inst:%3.1f ave:%3.1f sd:%3.1f max:%3.1f min:%3.1f\r\n",data[var_idx].name,\
                        data[var_idx].inst_value,\
                        data[var_idx].ave_value, \
                        data[var_idx].sd_value, \
                        data[var_idx].max_value, \
                        data[var_idx].min_value);
                #endif
            }
        }
    }
    return data;
}

//-----------------------------------------------------------------------------
//--Private functions----------------------------------------------------------
//-----------------------------------------------------------------------------

void _measure_read_sensor(void){
    for (uint8_t var_idx=0;var_idx<numberOfVars;var_idx++){
        if(data[var_idx].type==ANALOGVAR){
            switch(data[var_idx].variable){
                case TEMP_AMB:
                    data[var_idx].raw_value = analogRead(data[var_idx].pin);
                    data[var_idx].inst_value = _measure_unit_calc(var_idx, data[var_idx].sensor);
                    array_proc[TEMP_AMB]->push(data[var_idx].inst_value);                   
                    break;
                case TEMP_EXT:
                    data[var_idx].raw_value = analogRead(data[var_idx].pin);
                    data[var_idx].inst_value = _measure_unit_calc(var_idx, data[var_idx].sensor);
                    array_proc[TEMP_EXT]->push(data[var_idx].inst_value);                   
                    break;

            }
        }
    }
}


float _measure_unit_calc(uint8_t var_idx, uint16_t unit){
    float value=0;
    switch (unit){
        case TC1047:
            value=((((float)data[var_idx].raw_value /1024)-.5)/.01)*tc1047gain+tc1047offset; 
            break;
        case LM35:
            value=((float)data[var_idx].raw_value)*lm35gain+lm35offset; 
            break;
        case DHT22:
            value=data[var_idx].raw_value;
            break;
    }
    return value;
}

