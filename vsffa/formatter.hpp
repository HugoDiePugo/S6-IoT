#ifndef FORMATTER_H
#define FORMATTER_H

#include "measurement.hpp"
#include <TheThingsNetwork.h>
#include <stdint.h>
#include <assert.h>

#define VERSION (0b0001)

#define HEADER(cmd) (VERSION << 4 | cmd)

typedef enum {
  HEALTH = 0b0000,
  ALARM,
  THRESHOLD = 0b1000,
  PERIOD,
  RESET
} cmd_e;

class Formater {
private:
    Measurement* measurements;
    uint8_t amountOfMeasurements;
    TheThingsNetwork* ttn;
    uint8_t alarmsMask;

    uint32_t timeMinutes; //Minutes
    uint32_t lastHealthUpdate;
    uint32_t lastSample;
    uint32_t lastAlarm;

    uint16_t wakePeriod;
    uint16_t healthUpdatePeriod; //Minutes
    uint16_t samplePeriod; //Mintues
    uint16_t alarmPeriods[4]; //Minutes

public:
    // Constructor
    Formater(Measurement* measurements, uint8_t amountOfMeasurements, TheThingsNetwork* ttn)
        : measurements{measurements}, amountOfMeasurements{amountOfMeasurements}, ttn{ttn} {
            assert(amountOfMeasurements <= 4);
        }

    // Methods
    void Send(cmd_e cmd);
    void Receive(const uint8_t *payload, size_t size, port_t port);
};


#endif // FORMATTER_H