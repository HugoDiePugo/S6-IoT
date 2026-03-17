// Board: Arduino Leonardo

#include <TheThingsNetwork.h>
#include "formatter.hpp"
#include "measurement.hpp"

const char *appEui = "70B3D57ED004CFFB";
const char *appKey = "A7ACEC296DB8B83D02DD08CDE378845E";

#define loraSerial Serial1
#define debugSerial Serial
#define freqPlan TTN_FP_EU868

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

Measurement measurements[] = {
  {false, 10},
  {true, 20},
  {false, 30},
  {false, 70}
};

Formater formater(measurements, 4, &ttn);

void setup() {

  loraSerial.begin(57600);
  debugSerial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  while (!debugSerial && millis() < 10000);

  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);

  debugSerial.print("Power: ");
  debugSerial.print(ttn.getPower());
  debugSerial.println(" dBi");
}

void loop() {
  formater.Send(HEALTH);
  delay(10000);
  formater.Send(ALARM);
  delay(10000);
}

