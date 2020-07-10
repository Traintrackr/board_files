/* *************************
 *  Traintrackr Basics RGB
 *  traintrackr.io
 *  Richard Hawthorn
 *  2020-07-10
 */

#include <NeoPixelBrightnessBus.h>
NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp8266Uart1Ws2812xMethod> pixels(500);


void setup() {
  Serial.begin(115200);
  Serial.println("Traintrackr Basics RGB");

  //enable RGB data
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);

  //Setup pixels
  pixels.Begin();

  //setting the brightness low to start, so you don't blind yourself
  pixels.SetBrightness(30);

  //set all pixels off
  for (int i = 0; i<500; i++){
    pixels.SetPixelColor(i, RgbColor(0, 0, 0));
  }

  //output pixel data to LEDs
  pixels.Show();


}




void loop() {

  //turn on the first LED 
  //The first RGB led on the Traintrackr PCBs usually starts at 2, LEDs 0 and 1 are used to control the status lights
  pixels.SetPixelColor(2, RgbColor(255, 0, 0));
  pixels.Show();

  //wait a second
  delay(1000);

  //turn off the LED
  pixels.SetPixelColor(2, RgbColor(0, 0, 0));
  pixels.Show();

  //wait a second
  delay(1000);  

}
