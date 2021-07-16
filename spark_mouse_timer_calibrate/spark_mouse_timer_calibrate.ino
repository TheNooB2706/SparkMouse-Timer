//This sketch is used to get the value of the sensor when pressed. Upload this and open up a text editor. Then plug the DigiSpark in to type the value into the editor
//Warning: this type stuff

#include <DigiKeyboard.h>

#include <CapacitiveSensor.h>

CapacitiveSensor cs1 = CapacitiveSensor(1,0); //Setup cs object, pin 1 as send pin and pin0 as receive pin
CapacitiveSensor cs2 = CapacitiveSensor(1,2); //reuse pin1 for send pin and pin2 for receive

void setup() {
  cs1.reset_CS_AutoCal(); //calibrate sensor on start. Important to not touch the sensor during startup
  cs2.reset_CS_AutoCal();
  cs1.set_CS_AutocaL_Millis(0xFFFFFFFF); //Disable auto calibration of sensor during use
  cs2.set_CS_AutocaL_Millis(0xFFFFFFFF);
}

void loop() {
  long pad1 = cs1.capacitiveSensor(50); //get value of sensor1. 20 is an arbitrary value
  long pad2 = cs2.capacitiveSensor(50); //get value of sensor2
  DigiKeyboard.print("Sensor 1: ");
  DigiKeyboard.print(pad1);
  DigiKeyboard.print("; Sensor 2: ");
  DigiKeyboard.println(pad2);
  DigiKeyboard.delay(500);
}
