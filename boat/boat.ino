#include "hardware.h"
#include "sense.h"
#include "persist.h"
#include <PID_v1.h>

enum State {
   STRAIGHT,
   CORNER,
   STOPPED 
};

double sideWall=0, refSideWall=25, rudderAngle=0;
PID rudderCtrl(&sideWall, &rudderAngle, &refSideWall, 1, 0.1, 0.25, DIRECT);

double thrust; 

unsigned int now;
unsigned int tStateSwitch;
unsigned int tDetectCorner;
unsigned int tActuate;
unsigned int tDump;
void setup() {
   rudderCtrl.SetMode(AUTOMATIC);
   rudderCtrl.SetOutputLimits(-25, 25);
   rudderCtrl.SetSampleTime(POLLING_RATE*2);
   initHardware();
   Serial.begin(9600);

   now = millis();
   tStateSwitch = millis();
   tDetectCorner = millis();
   tActuate = millis();
   tDump = millis();
}

#define SPEED 100
#define MIN_TIME_IN_TURN 1000
#define MIN_TIME_IN_STRAIGHT 500

State state = STRAIGHT;
double frontWall = 0, angle = 0;
void loop() {
   now = millis();

   sense(&frontWall, &sideWall, &angle);

   switch(state) {

      case STRAIGHT:
         thrust = 40;

         rudderCtrl.Compute(sin(angle)*SPEED);

         /*if(now - tStateSwitch > 5000) {*/
            /*tStateSwitch = now;*/
            /*state = STOPPED;*/
         /*}*/

         if(now - tDetectCorner > POLLING_RATE) {
            tDetectCorner = now;
            if (detectCorner(frontWall) &&
                now - tStateSwitch > MIN_TIME_IN_STRAIGHT) {
               rudderCtrl.SetMode(MANUAL);
               tStateSwitch = now;
               state = CORNER;
            }
         }

         break;

      case CORNER:
         thrust = 40;
         rudderAngle = 30;
         if (detectStraight(frontWall) &&
             now - tStateSwitch > MIN_TIME_IN_TURN) {
            rudderCtrl.SetMode(AUTOMATIC);
            tStateSwitch = now;
            state = STRAIGHT;
         }
         break;
      case STOPPED:
         thrust = 0;
         rudderAngle = 0;
         break;
   }

   if(now - tActuate > 1) {
      tActuate = now;
      setThrust(thrust); setRudder(rudderAngle);
      /*setThrust(0); setRudder(0);*/
   }

   if(now - tDump > POLLING_RATE) {
      tDump = now;
      crap();
      persist(front, top, bottom);
   }
}

/*boolean detectCorner(int frontWall) {*/
   /*return frontWall <= 100;*/
/*}*/

int timesDetected = 0; 

boolean detectCorner(int frontWall) {
  if(frontWall <= 130) {
     timesDetected++;
  } else {
     timesDetected = 0;
  }
  return timesDetected >= 1;
}

boolean detectStraight(int frontWall) {
   return frontWall > 50;
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
   Serial.print(" ");
   Serial.print(sin(angle)*SPEED);
   Serial.println("");
}

