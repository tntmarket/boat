#include "persist.h"
#include <EEPROM.h>

boolean READ_ONLY = true;
boolean FILLED;

void start_writing() {
   READ_ONLY = false;
   /*FILLED = EEPROM.read(1001);*/
   FILLED = false;
}

void persist(double front, double top, double bottom,
             double rudderAngle, double thrust, double refSideWall) {
   if(READ_ONLY || FILLED) {
      return;
   }
   static int i = 0;
   EEPROM.write(i, round(front));
   EEPROM.write(i + 1, round(top));
   EEPROM.write(i + 2, round(bottom));
   EEPROM.write(i + 3, round(rudderAngle));
   EEPROM.write(i + 4, round(thrust));
   EEPROM.write(i + 5, round(refSideWall));
   i += 6;
   EEPROM.write(1000, i/6);
   if(i == MAX_EEPROM) {
      EEPROM.write(1001, 1); FILLED = true;
   }
   Serial.println(i);
}

void recall() {
   EEPROM.write(1001, 0); FILLED = false;
   last_value = EEPROM.read(1000)*6;
   for(int i = 0; i <= last_value ; i++) {
      data[i] = EEPROM.read(i);
   }
   for(int i = last_value+1; i <= MAX_EEPROM ; i++) {
      data[i] = 0;
   }
}

