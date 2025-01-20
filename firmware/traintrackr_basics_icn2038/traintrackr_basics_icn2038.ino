/* *************************
 *  Traintrackr basics when using the ICN2038 + (ICN2012 or SM5166PF) LED driver chips
 *  traintrackr.io
 *  Richard Hawthorn
 *  2025-01-20
 *  
 *  Board: ESP DEV module
 *  Flash Size: 4Mb
 *  Set partition scheme to minimal SPIFFS
 *  
 *  Library: https://github.com/mrcodetastic/ESP32-HUB75-MatrixPanel-DMA
 *  
 *  The display chips are set up for a maximum of 32 x 32 LEDs.  Although not all boards use the full use of this space, 
 *  and each board has it's own specific height and width.  For example the Large London board (TFL6) is 16 x 24.
 *   
 */

//LED pinout
#define LED_R1 25
#define LED_G1 26
#define LED_BL1 27
#define LED_R2 14
#define LED_G2 12
#define LED_BL2 13
#define LED_CH_A 23
#define LED_CH_B 19
#define LED_CH_C 5
#define LED_CH_D 17
#define LED_CH_E 18
#define LED_CLK 16
#define LED_LAT 4
#define LED_OE 15


#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

//placeholder for the matrix object
MatrixPanel_I2S_DMA *matrix = nullptr;


void setup() {

  Serial.begin(115200);
  Serial.println("");
  Serial.println(F("traintrackr basics"));
  Serial.flush();

  //setup the button inputs
  pinMode(0, INPUT_PULLUP); //setup button
  pinMode(36, INPUT); //mode button

  //Custom pin mapping for all pins
  HUB75_I2S_CFG::i2s_pins _pins={LED_R1, LED_G1, LED_BL1, LED_R2, LED_G2,LED_BL2, LED_CH_A, LED_CH_B, LED_CH_C, LED_CH_D, LED_CH_E, LED_LAT, LED_OE, LED_CLK };                   
  
  //Setup the matrix
  HUB75_I2S_CFG matrix_config(32, 64, 1, _pins); // width, height, chain length, pin mapping

  //Customise some of the matrix settings
  matrix_config.clkphase = 0; //this needs to be set to 0
  matrix_config.driver = HUB75_I2S_CFG::ICN2038S; 
  matrix_config.min_refresh_rate = 85; //default is 85
  matrix = new MatrixPanel_I2S_DMA(matrix_config);

  //set the LED brightness, max = 255
  matrix->setBrightness8(128);  

  // Allocate memory and start DMA display
  if( not matrix->begin() ){
      Serial.println(F("led driver error"));
  }

  //turn all LEDs on
  matrix->fillScreenRGB888(60, 60, 60);

  //wait for 2 seconds
  delay(2000);

  //turn all LEDs off
  matrix->fillScreenRGB888(0, 0, 0);

}




void updatePixelMatrix(int x, int y, int r, int g, int b){
  
  //invert the x axis
  x = 31 - x;

  //update the LED based on x y grid position, correcting for gama
  matrix->drawPixelRGB888(x, y, r, g, b);
  
}


void updatePixel(int pixel_number, int r, int g = false, int b = false){
  
  //calculate the LED based on pixel number
  int y = floor(pixel_number / 32);
  int x = pixel_number - (y * 32);

  //update that LED 
  updatePixelMatrix(x, y, r, g, b);
   
}

void loop() {

  //loop through the LEDs
  for (int i = 0; i <= 10; i++) {
    
    //turn this one on
    updatePixel(i, 60, 60, 60);

    //wait 300ms
    delay(300);
  }

  //wait 3 seconds
  delay(3000);

  //turn off all the LEDs
  matrix->fillScreenRGB888(0, 0, 0); 

}
