#define CUSTOM 1
#define BUNCH 2
#define MODE 3


//RGB mods
#define RAINBOW 1
#define FADE 2

void parse_header(unsigned char header, char *mode, bool *crc, unsigned int* len){
  *mode = header>>5;
  *crc = (header>>4 & 1);
  unsigned char llen[7];
  bool ext = (header>>3 & 1);

  if(ext){
    *len = 0;
    Serial.readBytes(llen,(header & 0b111));
    for(int j =0; j < (header & 0b111); j++){
      *len = (*len) + llen[j];
    }
  }else{
    *len = (header & 0b111);
  }

}

bool checksum(char * data, int len, char crc){
  char sum = 0;
  for(int i = 0; i < len; i++){
    sum ^= data[i];
  }
  return sum == crc;
}

void execute(CRGB leds[NUM_LEDS], char mode, unsigned char * data, int len){
  switch(mode){
    case CUSTOM:
      set_color_led(leds,data);
      actual_mod = 0;
      break;
    case BUNCH:
      setBunch(leds,data,len);
      actual_mod = 0;
      break;
    case MODE:
      mod_execute(leds, data, len);
      break;
    default:
       break;
          
  }
}

void mod_execute(CRGB leds[NUM_LEDS], char* data, int len){
  switch(data[0]){
    case FADE:
      if (actual_mod != FADE){
        actual_mod = FADE;
        global_speed = data[1];
        fade_init(leds);
      }

    default:
      break;
  }
}
