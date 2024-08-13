/*
 * Wrapper class for non-blocking led pulse functions
 * @author: Sebastien Eckersley-Maslin
 * @date: 12 Dec 2019
 */
#ifndef PULSE_H
#define PULSE_H

#include <Arduino.h>
#include <Output.h>

enum PulseMode_t
{
    PULSE_INACTIVE,
    PULSE_BREATHE,
    PULSE_HEARTBEAT,
    PULSE_FLASH,
    PULSE_STROBE,
    PULSE_BLINK,
    PULSE_TIMEOUT
};

class Pulse : public Output
{
    private:
        uint32_t _lastInterval;
        uint32_t _timeout;

        PulseMode_t _mode;
        PulseMode_t _modeOnTimeout;
        uint8_t _count;

        // even elements are ON, odd are OFF. In ms
        uint16_t _heartbeat[4] = {20, 100, 20, 2000};
        uint16_t _strobe[2] = {20, 1000};
        uint16_t _flash[2] = {500, 500};
        uint16_t _blink[2] = {125, 125};

        void _setMode(PulseMode_t mode);

    public:
        Pulse(void);
        Pulse(int p, bool s = LOW, bool i = false);

        /**
         * @brief Breath the led, pulse in and out using PWM
         */
        void breathe();

        /**
         * @brief Flash the led like a heart-beat
         */
        void heartbeat();

        /**
         * @brief Flash the led continously
         */
        void flash();

        /**
         * @brief Strobe the led
         */
        void strobe();

        /**
         * @brief Blink the led
         */
        void blink();

        /**
         * @brief Call this every loop to update the pulse led
         */
        void tick();

        /**
         * @brief stop flashing!
         */
        void stop();

        /**
         * @brief Turn the led ON
         *
         */
        void on(void);

        /**
         * @brief turn the led OFF
         *
         */
        void off(void);

        /**
         * @brief Turn the led ON and then timeout
         * @param timeout time to timeout (ms)
         * @param modeOnTimeout pulse mode to enable on timeout (Default PULSE_INACTIVE)
         */
        void timeout(uint32_t timeout, PulseMode_t modeOnTimeout = PULSE_INACTIVE);

        PulseMode_t getMode(void) { return this->_mode; };
};

#endif