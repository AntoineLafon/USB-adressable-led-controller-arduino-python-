void set_color_led(CRGB leds[NUM_LEDS], unsigned char * data){
  leds[data[0]].setRGB(data[1], data[2], data[3]);
  FastLED.show();
}


void setBunch(CRGB leds[NUM_LEDS],unsigned char * data, int len){
  int i = 0;
  char start;
  start = data[0];
  while (3*i < len){
    leds[min(start+i,NUM_LEDS-1)].setRGB(data[3*i+1],data[3*i +2],data[3*i+3]);
    i++;
  }
  FastLED.show();  
}
