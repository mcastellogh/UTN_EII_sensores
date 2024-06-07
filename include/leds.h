
#ifndef _leds_h_
#define _leds_h_

#include <Arduino.h>
#include "config.h"

//--Enumerations
enum FSM_MQTT_STATES {
    DISCONNECTED = 0,
    CONNECTED,
    RECONNECT,
    WAITTORECONNECT,
    WAITFORCONNECT,
    UNAVAILABLE_CONNECTION
};
          
enum FSM_LED_STATES{ 
    LED_ON = 0, 
    LED_OFF, 
    LED_STOP, 
    LED_WAIT_ON, 
    LED_WAIT_OFF
};

//--Prototypes
void led_welcome(void);
void led_blink(uint8_t ton, uint8_t toff, uint8_t led_pin);
void led_flash(uint8_t ton, uint8_t count, uint8_t led_pin);
void led_blink_FSM(uint8_t ton, uint8_t toff, uint8_t led_pin);

#endif