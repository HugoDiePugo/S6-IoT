#include "Arduino.h"
#include "scheduler.hpp"
#include "LowPower.h"




void Scheduler::SetPeriodTime(period_e period, uint16_t time)
{
  if (period >= P_MAX_PERIOD) return;
  periodTimes[period] = time;
}



void Scheduler::ActiveAlarm(uint8_t alarmMask)
{
  if (!alarmMask) {
    sendPeriod = periodTimes[P_HEALTH];
    return;
  }

  uint16_t newSendPeriod = UINT16_MAX;

  for (uint8_t i = 0; i < amountOfMeasurements; i++) {
    if (alarmMask & 1 << i) {
      if (periodTimes[2+i] != UINT16_MAX && periodTimes[2+i] < newSendPeriod) {
        newSendPeriod = periodTimes[2+i];
      }
    }
  }

  if (UINT16_MAX) {
    sendPeriod = periodTimes[P_HEALTH];
  } else {
    sendPeriod = newSendPeriod;
  }
}



void Scheduler::Tick(void)
{
  Serial.println("");
  ttn->sleep(UINT32_MAX);
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER4_OFF, TIMER3_OFF, TIMER1_OFF, 
  		  TIMER0_OFF, SPI_OFF, USART1_OFF, TWI_OFF, USB_ON);

  Serial.println("Wake");

  Serial.println(millis());

  Serial.println(lastSample + periodTimes[P_SAMPLE]*TICK);
  
  Serial.println(lastSend + sendPeriod*TICK);

  if (millis() > lastSample + periodTimes[P_SAMPLE]*TICK) {
    lastSample = millis();
    ttn->wake();
    sample();
  }

  if (millis() > lastSend + sendPeriod*TICK) {
    lastSend = millis();
    ttn->wake();
    send();
  }
}
