#include "hardware.h" 
#include "persist.h" 
#include <EEPROM.h>

int front_i = -6;
int top_i = -5;
int bottom_i = -4;

double getTop() {
   top_i = (top_i + 6)%MAX_EEPROM;
   return (double)data[top_i];
}

double getFront() {
   front_i = (front_i + 6)%MAX_EEPROM;
   return (double)data[front_i];
}

double getBottom() {
   bottom_i = (bottom_i + 6)%MAX_EEPROM;
   return (double)data[bottom_i];
}

void setThrust(int thrust) {
}

void setRudder(int angle) {
}

void initHardware() {
   recall();
   Serial.begin(115200);
}

