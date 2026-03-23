#include "measurement.h"

void Measurement::setThreshold(uint8_t thresh)
{
    threshold = thresh;
    return;
}

void Measurement::setMaxChange(uint8_t change)
{
    maxChange = change;
    return;
}

bool Measurement::gotTriggered()
{
    if(sensorType = BATT_SW) {triggered = (value <= threshold);}
    else {triggered = (value >= threshold);}
    
    return triggered;
}

void Measurement::addValue(uint8_t val)
{
    value = val;
}

uint8_t Measurement::getValue()
{
    return value;
}