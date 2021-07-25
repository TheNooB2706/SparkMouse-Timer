//This code is also known as the "Artificial Intelligence and Cloud algorithm". What? Don't get it? You have to (re)watch the advertisement: https://youtu.be/cwrDlWCdoEo
#include <CapacitiveSensor.h>
//THRESHOLD VARIABLE HERE
long threshold = 100; //Threshold value for the capacitive sensor, may need to be edited for specific case
//THRESHOLD VARIABLE HERE
CapacitiveSensor cs1 = CapacitiveSensor(1,0); //Setup cs object, pin 1 as send pin and pin0 as receive pin
CapacitiveSensor cs2 = CapacitiveSensor(1,2); //reuse pin1 for send pin and pin2 for receive
int previousState = 0; //This variable is used to store the previous state of sensor. 0=not pressed 1=pressed

//#include <usbdrv.h> //I assume these are not needed, not sure why they are automatically included (and it doesn't compile)
//#include <osccal.h>
#include <DigiMouse.h>
//#include <usbconfig.h>
//#include <usbconfig-prototype.h>
//#include <oddebug.h>
//#include <osctune.h>
//#include <usbportability.h>

void setup() {
  cs1.reset_CS_AutoCal(); //calibrate sensor on start. Important to not touch the sensor during startup
  cs2.reset_CS_AutoCal();
  cs1.set_CS_AutocaL_Millis(0xFFFFFFFF); //Disable auto calibration of sensor during use
  cs2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  DigiMouse.begin(); //Some setup before using the library
  DigiMouse.delay(500); //Give computer some time to recognise the device
}

void loop() {
  DigiMouse.update(); //Spam update everywhere!
  long pad1 = cs1.capacitiveSensor(60); //get value of sensor1. 80 is an arbitrary value (obtained after repeated testing, you may need to do your own test)
  DigiMouse.update();
  long pad2 = cs2.capacitiveSensor(60); //get value of sensor2
  DigiMouse.update();
  
  if (previousState == 0) { //if sensor is not previously pressed
    if ((pad1 > threshold) && (pad2 > threshold)) { //if sensor is pressed
      DigiMouse.setButtons(1<<0); //engage left click
      DigiMouse.update();
      previousState = 1; //set status to pressed
    }
  }
  else { //if sensor previously pressed
    if (not ((pad1 > threshold) && (pad2 > threshold))) { //if any sensor released
      DigiMouse.setButtons(0); //disengage left click
      DigiMouse.update();
      previousState = 0; //set status to released
    }
  }
}
