// Board: Arduino Leonardo

#include "TheThingsNetwork.h"
#include "formatter.hpp"
#include "measurement.hpp"
#include "scheduler.hpp"
#include "sensor.hpp"

const char *appEui = "70B3D57ED004CFFB";
const char *appKey = "A7ACEC296DB8B83D02DD08CDE378845E";

#define loraSerial Serial1
#define freqPlan TTN_FP_EU868

TheThingsNetwork ttn(loraSerial, Serial, freqPlan);

Measurement measurements[] = {
  {BATT_SW, 30, 10},
  {TEMP_POT, 50, 10},
  {HUMID_POT, 30, 255},
  {CO2_SW, 200, 20}
};

Potmeter temperature(A0, -10, 90);
Potmeter hummity(A1, 0, 100);

Button battery(8, 33, 28);
Button smoke(9, 40, 250);



void Send(void);
void Sample(void);

Scheduler scheduler(4, &ttn, Sample, Send);
Formater formater(measurements, 4, &ttn, &scheduler);

void Receive(const uint8_t *payload, size_t size, port_t port);


void setup() {

  Serial.begin(9600);
  while (!Serial && millis() < 10000);

  temperature.begin();
  hummity.begin();
  smoke.begin();
  battery.begin();

  loraSerial.begin(57600);

  ttn.onMessage(Receive);
  ttn.reset();



  Serial.println("-- STATUS");
  ttn.showStatus();

  Serial.println("-- JOIN");
  ttn.join(appEui, appKey);

  Serial.print("Power: ");
  Serial.print(ttn.getPower());
  Serial.println(" dBi");
}



void loop() {
  scheduler.Tick();
}



void Receive(const uint8_t *payload, size_t size, port_t port)
{
  formater.Receive(payload, size, port);
}



void Send(void)
{
  Serial.println("Send");
  formater.Send(HEALTH);
}



void Sample(void)
{
  static uint8_t prvAlarm = 0;

  Serial.println("Sample");

  measurements[BATT_SW].addValue(battery.readValue());
  measurements[TEMP_POT].addValue(temperature.readValue());
  measurements[HUMID_POT].addValue(hummity.readValue());
  measurements[CO2_SW].addValue(smoke.readValue());

  formater.Send(ALARM);
}
