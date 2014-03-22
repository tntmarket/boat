#include "hardware.h" 
#include "persist.h" 

#define N 120

double SENSOR_VALUES[N] = {
   180.0000, 65.0000,  65.0000,
   176.9231, 63.7179,  64.1026,
   173.8462, 62.4359,  63.2051,
   170.7692, 61.1538,  62.3077,
   167.6923, 59.8718,  61.4103,
   164.6154, 58.5897,  60.5128,
   161.5385, 57.3077,  59.6154,
   158.4615, 56.0256,  58.7179,
   155.3846, 54.7436,  57.8205,
   152.3077, 53.4615,  56.9231,
   149.2308, 52.1795,  56.0256,
   146.1538, 50.8974,  55.1282,
   143.0769, 49.6154,  54.2308,
   140.0000, 48.3333,  53.3333,
   136.9231, 47.0513,  52.4359,
   133.8462, 45.7692,  51.5385,
   130.7692, 44.4872,  50.6410,
   127.6923, 43.2051,  49.7436,
   124.6154, 41.9231,  48.8462,
   121.5385, 40.6410,  47.9487,
   118.4615, 39.3590,  47.0513,
   115.3846, 38.0769,  46.1538,
   112.3077, 36.7949,  45.2564,
   109.2308, 35.5128,  44.3590,
   106.1538, 34.2308,  43.4615,
   103.0769, 32.9487,  42.5641,
   100.0000, 31.6667,  41.6667,
    96.9231, 30.3846,  40.7692,
    93.8462, 29.1026,  39.8718,
    90.7692, 27.8205,  38.9744,
    87.6923, 26.5385,  38.0769,
    84.6154, 25.2564,  37.1795,
    81.5385, 23.9744,  36.2821,
    78.4615, 22.6923,  35.3846,
    75.3846, 21.4103,  34.4872,
    72.3077, 20.1282,  33.5897,
    69.2308, 18.8462,  32.6923,
    66.1538, 17.5641,  31.7949,
    63.0769, 16.2821,  30.8974,
    60.0000, 15.0000,  30.0000
};
   
int front_i = -3;
int top_i = -2;
int bottom_i = -1;

double getTop() {
   top_i = (top_i + 3)%N;
   return SENSOR_VALUES[top_i];
}

double getFront() {
   front_i = (front_i + 3)%N;
   return SENSOR_VALUES[front_i];
}

double getBottom() {
   bottom_i = (bottom_i + 3)%N;
   return SENSOR_VALUES[bottom_i];
}

void setThrust(int thrust) {
}

void setRudder(int angle) {
}

void initHardware() {
   start_writing();
   Serial.begin(9600);
}

