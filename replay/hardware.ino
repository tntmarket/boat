#include "hardware.h" 
#include "persist.h" 
#include <EEPROM.h>

int front_i = -3;
int top_i = -2;
int bottom_i = -1;

double getTop() {
   top_i = (top_i + 3)%MAX_EEPROM;
   return data[top_i];
}

double getFront() {
   front_i = (front_i + 3)%MAX_EEPROM;
   return data[front_i];
}

double getBottom() {
   bottom_i = (bottom_i + 3)%MAX_EEPROM;
   return data[bottom_i];
}

void setThrust(int thrust) {
}

void setRudder(int angle) {
}

void initHardware() {
   recall();
   Serial.begin(9600);
}

