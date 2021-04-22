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


int r_dir = -1;
int g_dir = 1;
int b_dir = -1;

void fade_init(CRGB leds[NUM_LEDS]){
  for(int i = 0; i != NUM_LEDS; i++){
    leds[i] = CRGB(255, 0, 127);
  }
}

void fade_step(CRGB leds[NUM_LEDS], int global_speed){

  if( millis() - timer < global_speed ){
    return;
  }

  timer = millis();
  
  CRGB color = leds[0];
  color.r = color.r + r_dir;
  color.g = color.g + g_dir;
  color.b = color.b + b_dir;
  
  if (color.r >= 255 || color.r <= 0) {
    r_dir = r_dir * -1;
  }

  if (color.g >= 255 || color.g <= 0) {
    g_dir = g_dir * -1;
  }

  if (color.b >= 255 || color.b <= 0) {
    b_dir = b_dir * -1;
  }

  for(int i = 0; i != NUM_LEDS; i++){
    leds[i] = color;
  }

  FastLED.show();
}

void rgb_handler(CRGB leds[NUM_LEDS]){
  switch(actual_mod){
    case FADE:
      fade_step(leds, global_speed);
      break;
    default:
      break;
  }
}
