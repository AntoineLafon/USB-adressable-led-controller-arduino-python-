

void rainbowCycle(int SpeedDelay, int incr) {
  byte *c = malloc( 3 * sizeof(byte));
  for(int i=0; i< NUM_LEDS; i++) {
    c=Wheel(((i * 256 / NUM_LEDS) + incr) & 255);
    setPixel(i, *c, *(c+1), *(c+2));
  }
  showStrip();
  delay(SpeedDelay);
}


void confirm(){
  Serial.println("OK");
}

byte *fade(byte *in){
   
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
 
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}
