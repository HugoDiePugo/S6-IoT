#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "TheThingsNetwork.h"
#include <stdint.h>


#define TICK (10000) //10 sec
// #define TICK (60000) //60 sec

typedef enum {
  P_SAMPLE,
  P_HEALTH,
  P_ALARM_0,
  P_ALARM_1,
  P_ALARM_2,
  P_ALARM_3,
  P_MAX_PERIOD
} period_e;

typedef void (*callback_t)(void); 

class Scheduler {
private:
  uint32_t lastSample = 0;
  uint32_t lastSend = 0;
  
  uint8_t amountOfMeasurements;
  uint16_t sendPeriod;
  uint16_t periodTimes[P_MAX_PERIOD] = {1, 1, 20, 2, UINT16_MAX, 4};

  TheThingsNetwork* ttn;

  callback_t sample;
  callback_t send;

public:
  Scheduler(uint8_t amountOfMeasurements, TheThingsNetwork* ttn, callback_t sample, callback_t send) : amountOfMeasurements{amountOfMeasurements}, ttn{ttn}, sample{sample}, send{send}{
    sendPeriod = periodTimes[P_HEALTH];
  }

  void SetPeriodTime(period_e period, uint16_t time);
  void ActiveAlarm(uint8_t alarmMask);
  void Tick(void);
};


#endif // SCHEDULER_H
