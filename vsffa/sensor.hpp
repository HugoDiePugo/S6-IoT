#include <Arduino.h>

// ===================== Button =====================
class Button {
private:
    uint8_t pin;
    int minValue;
    int maxValue;

public:
    Button(uint8_t buttonPin, int minVal, int maxVal) : pin(buttonPin) {
        minValue = minVal; 
        maxValue = maxVal;
    }

    void begin() {
        pinMode(pin, INPUT);
    }

    int8_t readValue() {
      if (digitalRead(pin)) {
        return minValue;
      } else {
        return maxValue;
      }      
    }
};

// ===================== Potmeter =====================
class Potmeter {
private:
    uint8_t pin;
    int minValue;
    int maxValue;

public:
    Potmeter(uint8_t potPin, int minVal, int maxVal) : pin(potPin) {
        minValue = minVal;
        maxValue = maxVal;
    }

    void begin() {}

    int readValue() {
        int value = analogRead(pin);
        return map(value, 0, 1023, minValue, maxValue);
    }
};
