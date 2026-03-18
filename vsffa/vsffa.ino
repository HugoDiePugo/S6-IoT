// Board: Arduino Leonardo

#include "TheThingsNetwork.h"
#include "formatter.hpp"
#include "measurement.hpp"
#include "scheduler.hpp"

const char *appEui = "70B3D57ED004CFFB";
const char *appKey = "A7ACEC296DB8B83D02DD08CDE378845E";

#define loraSerial Serial1
#define freqPlan TTN_FP_EU868

TheThingsNetwork ttn(loraSerial, Serial, freqPlan);

Measurement measurements[] = {
  {false, 10},
  {true, 20},
  {false, 30},
  {false, 70}
};

void Send(void);
void Sample(void);

Scheduler scheduler(4, &ttn, Sample, Send);
Formater formater(measurements, 4, &ttn, &scheduler);

void Receive(const uint8_t *payload, size_t size, port_t port);


void setup() {

  Serial.begin(9600);
  while (!Serial && millis() < 10000);

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
  // delay(16000);
  // LowPower.idle(SLEEP_8S, ADC_OFF, TIMER4_OFF, TIMER3_OFF, TIMER1_OFF, 
  // 		  TIMER0_OFF, SPI_OFF, USART1_OFF, TWI_OFF, USB_ON);
  // LowPower.idle(SLEEP_8S, ADC_OFF, TIMER4_OFF, TIMER3_OFF, TIMER1_OFF, 
  //     TIMER0_OFF, SPI_OFF, USART1_OFF, TWI_OFF, USB_ON);
  // ttn.wake();
  // formater.Send(HEALTH);
  // ttn.sleep(UINT32_MAX);
  // // delay(16000);
  // LowPower.idle(SLEEP_8S, ADC_OFF, TIMER4_OFF, TIMER3_OFF, TIMER1_OFF, 
  // 		  TIMER0_OFF, SPI_OFF, USART1_OFF, TWI_OFF, USB_ON);
  // LowPower.idle(SLEEP_8S, ADC_OFF, TIMER4_OFF, TIMER3_OFF, TIMER1_OFF, 
  //     TIMER0_OFF, SPI_OFF, USART1_OFF, TWI_OFF, USB_ON);
  // ttn.wake();
  // formater.Send(ALARM);
  // ttn.sleep(UINT32_MAX);
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
  Serial.println("Sample");
}
