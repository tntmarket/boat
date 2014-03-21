#include "sense.h"
#include "hardware.h"


enum ToSense {
   TOP,
   FRONT_SIDE 
};

ToSense nextSense = FRONT_SIDE;

double lastFront = 0;
void sense(double *frontWall, double *sideWall, double *angle, double *dFrontWall) {
   static unsigned int t = millis();
   static double LENGTH = 15;
   
   if(millis() - t > 40) {
      if(nextSense == TOP) {
         top = getTop(); 
         nextSense = FRONT_SIDE;
      } else {
         front = getFront();
         bottom = getBottom();
         nextSense = TOP;
      }
      t = millis();
      *angle = atan((top - bottom)/LENGTH);
      *sideWall = cos(*angle) * (top + bottom)/2;
      *frontWall = front;
      *dFrontWall = front - lastFront;

      lastFront = front;
   }
}
