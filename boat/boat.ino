#include "hardware.h"
#include "sense.h"
#include "persist.h"
#include <PID_v1.h>

enum State {
   STRAIGHT,
   CORNER,
   STOPPED 
};

double sideWall=0, refSideWall=20, rudderAngle=0;
PID rudderCtrl(&sideWall, &rudderAngle, &refSideWall, 1.4, 0, 0.2, DIRECT);

double thrust; 

void setup() {
   rudderCtrl.SetMode(AUTOMATIC);
   rudderCtrl.SetOutputLimits(-25, 25);
   rudderCtrl.SetSampleTime(100);
   initHardware();

   Serial.begin(9600);
}

#define SPEED 100
#define MIN_TIME_IN_TURN 1000
#define MIN_TIME_IN_STRAIGHT 1000

State state = STRAIGHT;
double frontWall = 0;
void loop() {
   static double angle = 0;

   sense(&frontWall, &sideWall, &angle);

   static unsigned int tStateSwitch = millis();
   static unsigned int tDetectCorner = millis();

   switch(state) {

      case STRAIGHT:
         thrust = 100;

         rudderCtrl.Compute(sin(angle)*SPEED);
         if(millis() - tStateSwitch > 3000) {
            state = STOPPED;
         }
         /*if(millis() - tDetectCorner > 100) {*/
            /*tDetectCorner = millis();*/
            /*if (detectCorner(frontWall) &&*/
                /*millis() - tStateSwitch > MIN_TIME_IN_STRAIGHT) {*/
               /*rudderCtrl.SetMode(MANUAL);*/
               /*tStateSwitch = millis();*/
               /*state = CORNER;*/
            /*}*/
         /*}*/
         break;

      case CORNER:
         thrust = 100; 
         rudderAngle = 35;
         if (detectStraight(frontWall) &&
             millis() - tStateSwitch > MIN_TIME_IN_TURN) {
            rudderCtrl.SetMode(AUTOMATIC);
            tStateSwitch = millis();
            state = STRAIGHT;
         }
         break;
      case STOPPED:
         setThrust(0); setRudder(0);
         return;
   }

   static unsigned int tActuate = millis();
   if(millis() - tActuate > 2) {
      tActuate = millis();
      setThrust(thrust); setRudder(rudderAngle);
   }

   static unsigned int tDump = millis();
   if(millis() - tDump > 100) {
      crap();
      tDump = millis();
      persist(frontWall, top, bottom);
   }
}

boolean detectCorner(int frontWall) {
   return frontWall <= 100;
}

boolean detectStraight(int frontWall) {
   return frontWall > 100;
}

void crap() {
   Serial.print(frontWall);
   Serial.print(" ");
   Serial.print(top);
   Serial.print(" ");
   Serial.print(bottom);
   Serial.print(" ");
   Serial.print(rudderAngle);
   Serial.print(" ");
   Serial.print(thrust);
   Serial.print(" ");
   Serial.print(refSideWall);
   Serial.print(" ");
   Serial.print(state);
   Serial.println("");
}

