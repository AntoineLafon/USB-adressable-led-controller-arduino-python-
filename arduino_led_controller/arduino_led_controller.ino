#include <FastLED.h>
#define NUM_LEDS 100
CRGB leds[NUM_LEDS];
#define PIN 3


#define FIXED 0
#define RAINBOW 1

byte *c;
byte command[5];
int mode;
int incr = 0;

bool readCommand(byte command[5]){
  if(Serial.available() >= 5){
    for(int i = 0; i<5; i++){
      command[i] = Serial.read();
    }
    return true;
  }
  return false;
}

void setup() {
  c = malloc( 3 * sizeof(byte));
  mode = 0;
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( 0x3C6DFF );
  Serial.begin(11200); 
}



void loop() {

  if(readCommand(command)){
    switch(command[0]){
      case 'B':
        mode = FIXED;
        c[2] = command[1];
        setAll(c[0], c[1], c[2]);
        confirm();
        break;
      case 'R':
        mode = FIXED;
        c[0] = command[1];
        setAll(c[0], c[1], c[2]);
        confirm();
        break;
      case 'G':
        mode = FIXED;
        c[1] = command[1];
        setAll(c[0], c[1], c[2]);
        confirm();
        break;
      case 'W':
        confirm();
        mode = RAINBOW;
      default:
        break;
    }
  }else{
    switch(mode){
      case RAINBOW:
      rainbowCycle(10, incr %(256 * 5));
      incr++;
      break;
        
      
    }
  }
  /*if (Serial.available() >= 2) {
    char command = Serial.read();
    byte parameter = Serial.read();

    switch(command){
      case 'B':
        b = parameter;
        setAll(r, g, b);
        confirm();
        break;
       case 'G':
          g = parameter;
          setAll(r, g, b);
          confirm();
          break;
       case 'R':
          r = parameter;
          setAll(r, g, b);
          confirm();
          break;
       case 'W':
          rainbowCycle(int(parameter));
          confirm();
          break;
       default:
        Serial.flush();
        break;
    }
  }*/

}

byte readNextValue(){
  return (Serial.available() > 0)? -1: Serial.read();
  
}


 void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}
