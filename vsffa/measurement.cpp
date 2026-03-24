#include "measurement.hpp"
#include "Arduino.h"



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

    if(sensor == BATT_SW || sensor == HUMID_POT) 
        triggered = (value <= threshold);
    else if (sensor == TEMP_POT)
        triggered = ((int8_t)value >= (int8_t)threshold);
    else
        triggered = (value >= threshold);
    
    triggered |= abs((int8_t)prev-(int8_t)value) >= maxChange;


    Serial.print("Triggered: ");
    Serial.println(triggered);
    Serial.println(value);
    Serial.println(threshold);

    return triggered;
}



void Measurement::addValue(uint8_t val)
{
    prev = value;
    value = val;

    if (startUp) {
        startUp = false;
        prev = value;
    }
}



uint8_t Measurement::getValue()
{
    return value;
}
