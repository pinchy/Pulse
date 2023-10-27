#include "Pulse.h"

Pulse::Pulse(void) {}
Pulse::Pulse(int p, bool s, bool i) : Output{p, s, i} {}

void Pulse::_setMode(PulseMode_t mode)
{
    if (this->_mode != mode)
    {
        this->_mode = mode;
        this->_count = 0;

        this->_lastInterval = millis();

        if (this->_mode != PULSE_INACTIVE) this->set(true);   // start the mode by turning the led on
    }
}

void Pulse::breathe() { this->_setMode(PULSE_BREATHE); }
void Pulse::strobe() { this->_setMode(PULSE_STROBE); }
void Pulse::heartbeat() { this->_setMode(PULSE_HEARTBEAT); }
void Pulse::flash() { this->_setMode(PULSE_FLASH); }
void Pulse::blink() { this->_setMode(PULSE_BLINK); }

void Pulse::stop()
{
    this->off();
    this->_mode = PULSE_INACTIVE;
}

void Pulse::on(void)
{
    this->_mode = PULSE_INACTIVE;
    this->set(true);
}

void Pulse::off(void)
{
    this->_mode = PULSE_INACTIVE;
    this->set(false);
}

void Pulse::timeout(uint32_t timeout, PulseMode_t modeOnTimeout)
{
    this->_timeout = timeout;
    this->_modeOnTimeout = modeOnTimeout;
    this->_setMode(PULSE_TIMEOUT);
}

void Pulse::tick()
{
    switch (this->_mode)
    {
        case PulseMode_t::PULSE_BREATHE:

            break;

        case PulseMode_t::PULSE_HEARTBEAT:
            if (millis() - this->_lastInterval >= this->_heartbeat[this->_count])
            {
                this->_lastInterval = millis();
                if (++this->_count >= (sizeof(this->_heartbeat) / sizeof(this->_heartbeat[0]))) this->_count = 0;
                this->set(!(this->_count % 2));   // even is on
            }
            break;

        case PulseMode_t::PULSE_FLASH:
            if (millis() - this->_lastInterval >= this->_flash[this->_count])
            {
                this->_lastInterval = millis();
                if (++this->_count >= (sizeof(this->_flash) / sizeof(this->_flash[0]))) this->_count = 0;
                this->set(!(this->_count % 2));   // even is on
            }
            break;

        case PulseMode_t::PULSE_STROBE:
            if (millis() - this->_lastInterval >= this->_strobe[this->_count])
            {
                this->_lastInterval = millis();
                if (++this->_count >= (sizeof(this->_strobe) / sizeof(this->_strobe[0]))) this->_count = 0;
                this->set(!(this->_count % 2));   // even is on
            }
            break;

        case PulseMode_t::PULSE_BLINK:
            if (millis() - this->_lastInterval >= this->_blink[this->_count])
            {
                this->_lastInterval = millis();
                if (++this->_count >= (sizeof(this->_blink) / sizeof(this->_blink[0]))) this->_count = 0;
                this->set(!(this->_count % 2));   // even is on
            }
            break;

        case PulseMode_t::PULSE_TIMEOUT:
            if (millis() - this->_lastInterval >= this->_timeout)
            {
                this->set(false);
                this->_setMode(this->_modeOnTimeout);
            }

        case PulseMode_t::PULSE_INACTIVE:
            break;
    }
}