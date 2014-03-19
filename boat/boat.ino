#include "hardware.h"
#include "sense.h"
#include "persist.h"
#include <PID_v1.h>

enum State {
   STRAIGHT,
   CORNER
};

double sideWall, refSideWall=30, rudderAngle; 
PID rudderCtrl(&sideWall, &rudderAngle, &refSideWall, 0.5, 0, 1.1, DIRECT);

double thrust; 

void setup() {
   rudderCtrl.SetMode(AUTOMATIC);
   rudderCtrl.SetOutputLimits(-25, 25);
   rudderCtrl.SetSampleTime(100);
   initHardware();
}

void loop() {
   static State state = STRAIGHT;
   static unsigned long stateSwitchTime = 0, MIN_TIME_IN_STATE = 1000;
   static double frontWall;

   sense(&frontWall, &sideWall);

   switch(state) {

      case STRAIGHT:
         thrust = 100;
         rudderCtrl.Compute();
         /*if (detectCorner(frontWall) &&*/
             /*millis() - stateSwitchTime > MIN_TIME_IN_STATE ) {*/
            /*rudderCtrl.SetMode(MANUAL);*/
            /*state = CORNER;*/
            /*stateSwitchTime = millis();*/
         /*}*/
         break;

      case CORNER:
         thrust = 100; 
         rudderAngle = 25;
         if (detectStraight(frontWall) && 
             millis() - stateSwitchTime > MIN_TIME_IN_STATE ) {
            rudderCtrl.SetMode(AUTOMATIC);
            state = STRAIGHT;
            stateSwitchTime = millis();
         }
         break;

   }

   setThrust(thrust);
   setRudder(rudderAngle);

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
   Serial.println("");
   persist(front, top, bottom, rudderAngle, thrust, refSideWall);
}

boolean detectCorner(int frontWall) {
   return frontWall <= 30;
}

boolean detectStraight(int frontWall) {
   return frontWall > 30;
}
