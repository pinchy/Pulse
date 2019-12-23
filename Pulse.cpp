#include "Pulse.h"
#include <Arduino.h>

Pulse::Pulse(int p, int s) : Output {p, s} {}

void Pulse::_setMode(Mode mode)
{
    if(this->_mode != mode)
    {
        this->_mode = mode;
        this->_count = 0;
        this->_lastInterval = millis();
        this->on();
    }
}

void Pulse::breathe() { this->_setMode(BREATHE); }
void Pulse::strobe() { this->_setMode(STROBE); }
void Pulse::heartbeat() { this->_setMode(HEARTBEAT); }
void Pulse::flash() { this->_setMode(FLASH); }

void Pulse::stop()
{
    this->off();
    this->_mode = INACTIVE;
}

void Pulse::update()
{
    switch (this->_mode)
    {
        case BREATHE:

            

        break;

        case HEARTBEAT:
            if(millis() - this->_lastInterval >= this->_heartbeat[this->_count])
            {
                this->toggle();
                this->_lastInterval = millis();
                if(++this->_count >= (sizeof(this->_heartbeat) / sizeof(this->_heartbeat[0]))) this->_count = 0;
            }
        break;
        
        case FLASH:
            if(millis() - this->_lastInterval >= this->_flash[this->_count])
            {
                this->toggle();
                this->_lastInterval = millis();
                if(++this->_count >= (sizeof(this->_flash) / sizeof(this->_flash[0]))) this->_count = 0;
            }
        break;

        case STROBE:
            if(millis() - this->_lastInterval >= this->_strobe[this->_count])
            {
                this->toggle();
                this->_lastInterval = millis();
                if(++this->_count >= (sizeof(this->_strobe) / sizeof(this->_strobe[0]))) this->_count = 0;
            }
        break;

        case INACTIVE:
        break;

    }

}