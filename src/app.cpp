/*********************************************************************************
 * 
 *                       ELECTRONICA II UTN - FRRO                                *
 * 
 * *******************************************************************************/

//===================[File header]================================================
// File:                app.cpp
// Author:              Marcelo Castello (https://github.com/mcastellogh)
// Licence:             GPLV3+
// Version:             1.0.0
// Date:                Mayo 2024
// Info:                Proyect template for Electrónica II

//====================[Use & storage]============================================
// PCB:                 NodeMCU 
// Plataforma:          ESP8266  
// Use:                 Template
// Folder:              template_EII_V1
// Proyect name:        template_EII_V1

//====================[ToDo]=====================================================     
//        
//
//
//====================[Bugs]=====================================================     
//     
//                   
//
//====================[Commits]==================================================     
//
// Last commit:
//
//===================[End file header]===========================================


//--Includes
#include "app.h"


//--Local variables
uint16_t led_delay=200;
Data * dataToPus;

//--Extern variables
extern uint8_t var_count;

//--Functions
void App_loop(void){
    dataToPus=measure_loop();
    Serial.printf("%s: inst:%3.1f ave:%3.1f sd:%3.1f max:%3.1f min:%3.1f\r\n",dataToPus[TEMP_AMB].name, dataToPus[TEMP_AMB].inst_value, dataToPus[TEMP_AMB].ave_value,dataToPus[TEMP_AMB].sd_value,dataToPus[TEMP_AMB].max_value,dataToPus[TEMP_AMB].min_value);
    delay(200);
}