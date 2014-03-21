#include "hardware.h"
#include "sense.h"
#include "persist.h"
#include <PID_v1.h>

enum State {
   STRAIGHT,
   CORNER
};

double sideWall=0, refSideWall=30, rudderAngle=0;
PID rudderCtrl(&sideWall, &rudderAngle, &refSideWall, 1.5, 0, 0.1, DIRECT);


double thrust; 

void setup() {
   rudderCtrl.SetMode(AUTOMATIC);
   rudderCtrl.SetOutputLimits(-24, 25);
   rudderCtrl.SetSampleTime(100);
   initHardware();

   Serial.begin(9600);
}

#define SPEED 100
#define MIN_TIME_IN_STATE 1000

State state = STRAIGHT;
double dFrontWall;
void loop() {
   static double frontWall = 0, angle = 0;

   sense(&frontWall, &sideWall, &angle, &dFrontWall);

   static unsigned int tStateSwitch = millis();
   static unsigned int tDetectCorner = millis();

   switch(state) {

      case STRAIGHT:
         thrust = 200;

         /*if(angle > M_PI/6) {*/
            /*rudderCtrl.SetMode(MANUAL);*/
            /*rudderAngle = 0;*/
         /*} else if(angle < -M_PI/6) {*/
            /*rudderCtrl.SetMode(MANUAL);*/
            /*rudderAngle = 0;*/
         /*} else {*/
            /*rudderCtrl.SetMode(AUTOMATIC);*/
            /*rudderCtrl.Compute(sin(angle)*SPEED);*/
         /*}*/

         rudderCtrl.Compute(sin(angle)*SPEED);

         if(millis() - tDetectCorner > 100) {
            tDetectCorner = millis();
            if (detectCorner(frontWall, dFrontWall) &&
                millis() - tStateSwitch > MIN_TIME_IN_STATE) {
               rudderCtrl.SetMode(MANUAL);
               tStateSwitch = millis();
               state = CORNER;
            }
         }
         break;

      case CORNER:
         thrust = 255; 
         rudderAngle = 35;
         if (detectStraight(frontWall, dFrontWall) &&
             millis() - tStateSwitch > MIN_TIME_IN_STATE) {
            rudderCtrl.SetMode(AUTOMATIC);
            tStateSwitch = millis();
            state = STRAIGHT;
         }
         break;

   }

   static unsigned int tActuate = millis();
   if(millis() - tActuate > 2) {
      tActuate = millis();
      setThrust(thrust); setRudder(rudderAngle);
      /*setThrust(0); setRudder(0);*/
   }

   static unsigned int tDump = millis();
   if(millis() - tDump > 100) {
      crap();
      tDump = millis();
      persist(front, top, bottom, rudderAngle, thrust, refSideWall);
   }
}

void crap() {
   Serial.print(front);
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
   Serial.print(" ");
   Serial.print(dFrontWall);
   Serial.println("");
}

int timesDetected = 0; 
boolean detectCorner(int frontWall, int dFrontWall) {
   if(frontWall <= 100 && frontWall > 50) {
      timesDetected++;
   } else {
      timesDetected = 0;
   }
   return timesDetected > 6;
}

boolean detectStraight(int frontWall, int dFrontWall) {
   /*return dFrontWall > 10;*/
   return frontWall > 100;
}
