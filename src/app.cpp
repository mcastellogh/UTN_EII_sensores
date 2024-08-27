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
// Info:                Project 'sensores' for Electrónica II

//====================[Use & storage]============================================
// PCB:                 NodeMCU 
// Plataforma:          ESP8266  
// Use:                 measures
// Folder:              sensores
// Proyect name:        sensores

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
Data * dataToPush;

//--Main application
void App_loop(void){
    dataToPush=measure_loop();
    if(dataToPush[TEMP_AMB].procesed){
        Serial.printf("%s: inst:%3.1f ave:%3.1f sd:%3.1f max:%3.1f min:%3.1f\r\n",dataToPush[TEMP_AMB].name, dataToPush[TEMP_AMB].inst_value, dataToPush[TEMP_AMB].ave_value,dataToPush[TEMP_AMB].sd_value,dataToPush[TEMP_AMB].max_value,dataToPush[TEMP_AMB].min_value);
        dataToPush[TEMP_AMB].procesed=false;
    }
    if(dataToPush[TEMP_EXT].procesed){
        Serial.printf("%s: inst:%3.1f ave:%3.1f sd:%3.1f max:%3.1f min:%3.1f\r\n",dataToPush[TEMP_EXT].name, dataToPush[TEMP_EXT].inst_value, dataToPush[TEMP_EXT].ave_value,dataToPush[TEMP_EXT].sd_value,dataToPush[TEMP_EXT].max_value,dataToPush[TEMP_EXT].min_value);
        dataToPush[TEMP_EXT].procesed=false;
    }
    delay(200);
}