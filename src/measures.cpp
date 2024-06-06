//--Measures external sensors


#include "measures.h"

//--Local variables
bool flag_push=0;
float lm35gain=1;
float lm35offset=0;
float tc1047gain=1;
float tc1047offset=0;
uint32_t msec_an_reg;
uint32_t msec_an_sample;

//--Extern variables
extern Config config;


//--Create dataToPush array with variables to measure
//--Example:
//  "Humedad", 0, 0, 0, 0, RH, DIGITALVAR, DHT22_PIN
Data dataToPush[] = {
    // name, raw_value, inst_value, ave_value, sd_value, max_value, min_value, sensor, type, pin
    "Temperatura ambiente", 0, 0, 0, 0, 0, 0, TC1047, ANALOGVAR, TEMP_AMB_PIN,
    "Temperatura exterior", 0, 0, 0, 0, 0, 0, TC1047, ANALOGVAR, TEMP_EXT_PIN
};



//--Calculate number of variables in Data Structure
uint8_t numberDataToPush = sizeof(dataToPush) / sizeof(dataToPush[0]);

Process proc[2];

//--Create temp_proc objet to calculate average, max, min & sd for temperature readings
Average<float> temp_amb_proc(600);


//-----------------------------------------------------------------------------
//--Public functions-----------------------------------------------------------
//-----------------------------------------------------------------------------


void measure_init(void){
    msec_an_reg=millis();
    msec_an_sample=millis();
}

uint8_t measure_count(void){
    return numberDataToPush;
}

Data * measure_loop(void){
    if((millis()-msec_an_sample)>=MAX_mSEC_SAMPLE_AN){
        #ifdef DEBUG_MEAS
            Serial.println("Take a sample");
        #endif
        measure_read_sensor();
        msec_an_sample=millis();
    }
    if((millis()-msec_an_reg)>=MAX_mSEC_AVE_AN){
        #ifdef DEBUG_MEAS
            Serial.println("Process...");
        #endif
        for (uint8_t reg_idx=0;reg_idx<numberDataToPush;reg_idx++){
            if(dataToPush[reg_idx].type==ANALOGVAR){
                dataToPush[reg_idx].ave_value=temp_amb_proc.mean();
                dataToPush[reg_idx].sd_value=temp_amb_proc.stddev();
                dataToPush[reg_idx].max_value=temp_amb_proc.maximum();
                dataToPush[reg_idx].min_value=temp_amb_proc.minimum();        
                flag_push=1;
                msec_an_reg=millis();
                #ifdef DEBUG_MEAS
                    //Serial.printf("%s: inst:%3.1f ave:%3.1f sd:%3.1f max:%3.1f min:%3.1f\r\n",dataToPush[reg_idx].name,\
                        dataToPush[reg_idx].inst_value,\
                        dataToPush[reg_idx].ave_value, \
                        dataToPush[reg_idx].sd_value, \
                        dataToPush[reg_idx].max_value, \
                        dataToPush[reg_idx].min_value);
                #endif
            }
        }
    }
    return dataToPush;
}

//-----------------------------------------------------------------------------
//--Private functions----------------------------------------------------------
//-----------------------------------------------------------------------------


void measure_read_sensor(void){
    for (uint8_t reg_idx=0;reg_idx<numberDataToPush;reg_idx++){
        if(dataToPush[reg_idx].type==ANALOGVAR){
            dataToPush[reg_idx].raw_value = analogRead(dataToPush[reg_idx].pin);
            dataToPush[reg_idx].inst_value = measure_unit_calc(reg_idx, dataToPush[reg_idx].sensor);
            temp_amb_proc.push(dataToPush[reg_idx].inst_value);           
            //proc[reg_idx].pr.push(dataToPush[reg_idx].inst_value);           
        }
    }
}


float measure_unit_calc(uint8_t reg_idx, uint16_t unit){
    float value=0;
    switch (unit){
        case TC1047:
            value=((((float)dataToPush[reg_idx].raw_value /1024)-.5)/.01)*tc1047gain+tc1047offset; 
            break;
        case LM35:
            value=((float)dataToPush[reg_idx].raw_value)*lm35gain+lm35offset; 
            break;
        case DHT22:
            value=dataToPush[reg_idx].raw_value;
            break;
    }
    return value;
}

