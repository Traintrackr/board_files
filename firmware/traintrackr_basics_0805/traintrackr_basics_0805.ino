/* *************************
 *  Traintrackr Basics 0805
 *  traintrackr.io
 *  Richard Hawthorn
 *  2020-07-10
 */

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

// define led chip i2c addresses
int i2c_addresses[4] = {0x70, 0x74, 0x72, 0x71};

Adafruit_LEDBackpack matrix = Adafruit_LEDBackpack();
Adafruit_LEDBackpack matrix2 = Adafruit_LEDBackpack();
Adafruit_LEDBackpack matrix3 = Adafruit_LEDBackpack();
Adafruit_LEDBackpack matrix4 = Adafruit_LEDBackpack();


void setup() {
  Serial.begin(115200);
  Serial.println("Traintrackr Basics 0805");

  //setup the matrix chips
  matrix.begin(i2c_addresses[0]);
  matrix2.begin(i2c_addresses[1]);
  matrix3.begin(i2c_addresses[2]);
  matrix4.begin(i2c_addresses[3]);

  //set brightness
  matrix.setBrightness(4);
  matrix2.setBrightness(4);
  matrix3.setBrightness(4);
  matrix4.setBrightness(4);

  //write to display
  matrix.writeDisplay();
  matrix2.writeDisplay();
  matrix3.writeDisplay();
  matrix4.writeDisplay();

}




void loop() {

  //turn on the first LED
  matrix.displaybuffer[0] = 0x0001;
  matrix.writeDisplay();

  //wait a second
  delay(1000);

  //turn off the LED
  matrix.displaybuffer[0] = 0x0000;
  matrix.writeDisplay();

  //wait a second
  delay(1000);  

}
