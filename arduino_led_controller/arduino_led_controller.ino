#include <FastLED.h>

#define PIN 7
#define NUM_LEDS 99

CRGB leds[NUM_LEDS];

char header;
char mode;
unsigned int len;
bool ack;
unsigned char data[3*NUM_LEDS];
char actual_mod;
int global_speed = 0;
unsigned long timer = 0;
int lread;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(PIN, OUTPUT);
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( 0x3C6DFF );

}



void loop() {
 if(Serial.available()> 0){
   header = Serial.read();
   parse_header(header, &mode, &ack, &len);
   lread = Serial.readBytes(data,len);
   if (ack){
    while(Serial.available() > 0) {
      char t = Serial.read();
    }
    if (lread == len){
      Serial.write(~header);
    }else{
      Serial.write(1);
    }
   }
   execute(leds, mode, data, len);
 }

 rgb_handler(leds);


 

 
}
