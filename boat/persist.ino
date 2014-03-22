#include "persist.h"
#include <EEPROM.h>

boolean READ_ONLY = true;
boolean FILLED = false;

void start_writing() {
   delay(2000);
   READ_ONLY = false;
   /*FILLED = EEPROM.read(1001);*/
}

void persist(double front, double top, double bottom) {
   if(READ_ONLY || FILLED) {
      return;
   }
   static int i = 0;
   EEPROM.write(i    , round(front));
   EEPROM.write(i + 1, round(top));
   EEPROM.write(i + 2, round(bottom));
   i += 3;
   EEPROM.write(1000, i/3);
   if(i == MAX_EEPROM) {
      EEPROM.write(1001, 1); FILLED = true;
   }
   Serial.println(i);
}

void recall() {
   /*EEPROM.write(1001, 0); FILLED = false;*/
   last_value = EEPROM.read(1000)*3;
   for(int i = 0; i <= last_value ; i++) {
      data[i] = EEPROM.read(i);
   }
   for(int i = last_value+1; i <= MAX_EEPROM ; i++) {
      data[i] = 0;
   }
}

