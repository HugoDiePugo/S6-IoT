#include <stdint.h>
#include "formatter.hpp"

#include <Arduino.h>


void Formater::Send(cmd_e cmd)
{
  uint8_t payload[10];

  if (cmd & 0b1000) return;

  uint8_t i = 0;
  payload[i++] = HEADER(cmd);
  if (cmd == ALARM) {
    for (uint8_t j = 0; j < amountOfMeasurements; j++) {
      alarmsMask |= measurements[j].GotTriggered() << j;
      scheduler->ActiveAlarm(alarmsMask);
    }
    payload[i++] = alarmsMask;
  }

  for (uint8_t j = 0; j < amountOfMeasurements; j++) {
    payload[i++] = measurements[j].GetValue();
  }

  ttn->sendBytes(payload, i);

  for(int j = 0; j < i; j++)
  {
    Serial.print(payload[j]);
    Serial.print('-');
  }
  Serial.println("");

  Serial.println("Payload sent");
}



void Formater::Receive(const uint8_t *payload, size_t size, port_t port)
{
    uint8_t i = 0;
    cmd_e cmd = (cmd_e)(payload[i++]&0b1111);
    Serial.print("New message: ");
    Serial.println(cmd);

    switch (cmd) {
    case RESET:
      alarmsMask = 0;
      break;
    case THRESHOLD:
    {
      if (size < 2 + 2*amountOfMeasurements) break;

      uint8_t changedMask = payload[i++];
      for (uint8_t j = 0; j < 2*amountOfMeasurements; j++) {
        Serial.print("Offset: ");
        Serial.println(j>>1);
        if (changedMask & 1) {
          if (j & 1) {
            Serial.print("maxChange: ");
            Serial.println(payload[i]);
            measurements[j>>1].SetMaxChange(payload[i]);
          } else {
            Serial.print("Threshold: ");
            Serial.println(payload[i]);
            measurements[j>>1].SetThreshold(payload[i]);
          }
        }
        i++;
        changedMask = changedMask >> 1;
      }
      break;
    }
    case PERIOD:
    {
      if (size < 1 + 2*(amountOfMeasurements+2)) break;

      uint8_t changedMask = payload[i++];
      uint16_t* data = (uint16_t*)&payload[i];
      for (uint8_t j = 0; j < amountOfMeasurements+2; j++) {
        Serial.print("Offset: ");
        Serial.println(j);
        if (changedMask & 1) {
            Serial.print("period: ");
            Serial.println(data[j] >> 8 | data[j] << 8);
            scheduler->SetPeriodTime((period_e)j, data[j]);
        }
        changedMask = changedMask >> 1;
      }
      scheduler->ActiveAlarm(alarmsMask);
      break;
    }
  }
}
