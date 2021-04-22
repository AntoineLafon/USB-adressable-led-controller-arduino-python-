#include <FastLED.h>

#define PIN 7
#define NUM_LEDS 99

CRGB leds[NUM_LEDS];

char header;
char mode;
unsigned int len;
bool crc;
unsigned char data[3*NUM_LEDS];
int lcrc;

char actual_mod;
int global_speed = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(PIN, OUTPUT);
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( 0x3C6DFF );
}



void loop() {
 if(Serial.available()){
   header = Serial.read();
   parse_header(header, &mode, &crc, &len);
   lcrc = Serial.readBytes(data,len + (int)crc);
   if ((lcrc == len + (int)crc) && (!crc || checksum(data, len, data[len]))){
     execute(leds, mode, data, len);
   }
 }

 rgb_handler(leds);

 
}
