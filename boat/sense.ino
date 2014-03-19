#include "sense.h"
#include "hardware.h"

void sense(double *frontWall, double *sideWall) {

   delay(50);
   top = getTop(); 
   delay(50);
   front = getFront();
   bottom = getBottom();

   *sideWall = cos(angle(top, bottom)) * (top + bottom)/2;
   *frontWall = cos(angle(top, bottom)) * front;
}

double angle(double top, double bottom) {
   static double LENGTH = 15;
   return atan((top - bottom)/LENGTH);
}
