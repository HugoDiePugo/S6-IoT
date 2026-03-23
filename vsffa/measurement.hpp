#ifndef MEASUREMENT_H
#define MEASUREMENT_H

enum sensorType
{
    HUMID_POT,
    TEMP_POT,
    CO2_SW,
    BATT_SW
}

class Measurement
{
    public:
        sensorType sensor;
        uint8_t threshold;
        uint8_t maxChange;
        uint8_t value = 0;
        uint8_t prev = 0;
        bool triggered = false;

        Measurement(sensorType s, uint8_t t, uint8_t c) : sensor(s), threshold(t), maxChange(c) {}
        void setThreshold(uint8_t thresh);
        void setMaxChange(uint8_t change);
        bool gotTriggered();
        void addValue(uint8_t val);
        uint8_t getValue();
}

#endif