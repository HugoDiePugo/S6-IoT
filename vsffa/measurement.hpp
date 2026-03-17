#include <stdint.h>
#ifndef MEASUREMENT_H
#define MEASUREMENT_H

class Measurement {
private:
    uint8_t threshold;
    uint8_t maxChange;
    uint8_t value;
    uint8_t prv;
    bool triggered;

public:
    // Constructors
    Measurement(bool triggered, uint8_t value) : triggered{triggered}, value{value} {}

    // Setters
    void SetThreshold(uint8_t threshold);
    void SetMaxChange(uint8_t maxChange);

    // Behavior
    bool GotTriggered() {
      return triggered;
    };

    // Value handling
    void AddValue(uint8_t value);
    uint8_t GetValue() {
      return value;
    };
};

#endif // MEASUREMENT_H