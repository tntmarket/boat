#include "hardware.h" 
#include "persist.h" 
#include <NewPing.h>
#include <Servo.h>

double cm(int ping, int max) {
   return ping ? ((double)ping / (double)US_ROUNDTRIP_CM) : max;
}

#define MAX_DISTANCE_FRONT 200
#define FRONT_TRIGGER_PIN 7
#define FRONT_ECHO_PIN  6
double getFront() {
   static NewPing front(FRONT_TRIGGER_PIN,
                        FRONT_ECHO_PIN,
                        MAX_DISTANCE_FRONT);
   return cm(front.ping(), MAX_DISTANCE_FRONT);
}

#define MAX_DISTANCE_SIDE 100
#define TOP_TRIGGER_PIN 11
#define TOP_ECHO_PIN  12
double getTop() {
   static NewPing top(TOP_TRIGGER_PIN,
                      TOP_ECHO_PIN,
                      MAX_DISTANCE_SIDE);
   return cm(top.ping(), MAX_DISTANCE_SIDE);
}

#define BOTTOM_TRIGGER_PIN 4
#define BOTTOM_ECHO_PIN  5
double getBottom() {
   static NewPing bottom(BOTTOM_TRIGGER_PIN,
                         BOTTOM_ECHO_PIN,
                         MAX_DISTANCE_SIDE);
   return cm(bottom.ping(), MAX_DISTANCE_SIDE);
}

#define THRUST_PIN 3
void setThrust(int thrust) {
   analogWrite(THRUST_PIN, thrust);
}

#define RUDDER_PIN 9
Servo rudder;
void setRudder(int angle) {
   rudder.write(105 - angle);
}

#define I4_PIN 1
#define I3_PIN 2
void initHardware() {
   pinMode(RUDDER_PIN, OUTPUT);
   rudder.attach(RUDDER_PIN);

   pinMode(THRUST_PIN, OUTPUT);
   pinMode(I4_PIN, OUTPUT);
   pinMode(I3_PIN, OUTPUT);
   digitalWrite(I4_PIN, LOW);
   digitalWrite(I3_PIN, HIGH);

   setThrust(0);
   setRudder(0);

   /*start_writing()*/
   /*Serial.begin(115200);*/
}

