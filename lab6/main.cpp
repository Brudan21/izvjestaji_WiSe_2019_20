#include "Sensors.h"
#include <LowPower.h>

SENSORS sensor;

typedef enum
{
  READ_SERIAL,
  SLEEP,
  RADIO_COMM,
  READ_SENSORS,
} StateType;
void wakeup(){

}


void setup()
{
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2),wakeup,RISING);
  sensor.DHT_init();
  sensor.BH1750_init();
}
StateType state = READ_SERIAL;
void loop()
{

  switch (state)
  {
  case READ_SERIAL:
    delay(1);
    //Run state machine code
    //za sada mozete ostaviti prazno

    //Move to the next state
    state = READ_SENSORS;
    break;
  case READ_SENSORS:
    sensor.readTempHum();
    sensor.readLight();
    //Run state machine code

    //Move to the next state
    state = RADIO_COMM;
    break;
  case RADIO_COMM:
    //Run state machine code

    //Move to the next state
    state = SLEEP;
    break;
  case SLEEP:
    delay(50);
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    delay(50);
    state = READ_SERIAL;
    break;
  }
}
