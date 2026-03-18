#ifndef FORMATTER_H
#define FORMATTER_H

#include "measurement.hpp"
#include "scheduler.hpp"
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
    Scheduler* scheduler;

public:
    // Constructor
    Formater(Measurement* measurements, uint8_t amountOfMeasurements, TheThingsNetwork* ttn, Scheduler* scheduler)
        : measurements{measurements}, amountOfMeasurements{amountOfMeasurements}, ttn{ttn}, scheduler{scheduler} {
            assert(amountOfMeasurements <= 4);
        }

    // Methods
    void Send(cmd_e cmd);
    void Receive(const uint8_t *payload, size_t size, port_t port);
};


#endif // FORMATTER_H