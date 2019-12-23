/*
 * Wrapper class for non-blocking led pulse functions
 * @author: Sebastien Eckersley-Maslin
 * @date: 12 Dec 2019
 */
#ifndef PULSE_H
#define PULSE_H

#include "Output.h"
#include "Arduino.h"

enum Mode {INACTIVE, BREATHE, HEARTBEAT, FLASH, STROBE};

class Pulse : public Output
{
    private:
        uint32_t _lastInterval;
        Mode _mode;
        uint8_t _count;    

        // even elements are ON, odd are OFF. In ms
        uint16_t _heartbeat[4] = {20, 100, 20, 2000};
        uint16_t _strobe[2] = {20, 1000};
        uint16_t _flash[2] = {500, 500};

        void _setMode(Mode mode);           

    public:
    

        Pulse(int p, int s);

        /* 
         * Breath the led, pulse in and out using PWM
         */
        void breathe();

        /* 
         * Flash the led like a heart-beat
         */
        void heartbeat();

        /* 
         * Flash the led continously
         */
        void flash();

        /* 
         * Strobe the led
         */
        void strobe();
        
        /* 
         * Call this every loop to update the pulse led
         */
        void update();

        /*
         * stop flashing!
         */
        void stop();
        
}; 

#endif