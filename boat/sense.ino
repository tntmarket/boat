#include "sense.h"
#include "hardware.h"


enum ToSense {
   TOP,
   FRONT_SIDE 
};

ToSense nextSense = FRONT_SIDE;

unsigned int tSense = now; 
double LENGTH = 15;
double FILTER_THRESHOLD_FRONT = 40;
double FILTER_THRESHOLD = 100;
void sense(double *frontWall, double *sideWall, double *angle) {
   double newFront = front,
          newTop = top,
          newBottom = bottom;
   if(now - tSense > POLLING_RATE) {
      if(nextSense == TOP) {
         newFront = getFront();
         newTop = getTop(); 
         nextSense = FRONT_SIDE;
      } else {
         newFront = getFront();
         newBottom = getBottom();
         nextSense = TOP;
      }
      tSense = now;

      front =  newFront  > (front  - FILTER_THRESHOLD_FRONT) ? newFront  : front;
      top =    newTop    > (top    - FILTER_THRESHOLD      ) ? newTop    : top;
      bottom = newBottom > (bottom - FILTER_THRESHOLD      ) ? newBottom : bottom;

      *angle = atan((top - bottom)/LENGTH);
      *frontWall = front;
      *sideWall = cos(*angle) * (top + bottom)/2;
   }
}


/*static double a = 1;*/
/*double lastFront = 0;*/
/*double expAverageFront = -1;*/
/*void filter() {*/
   /*if(expAverageFront == -1) {*/
      /*expAverageFront = front;*/
   /*} else {*/
      /*expAverageFront = a*lastFront + (1-a)*expAverageFront;*/
   /*}*/

   /**frontWall = expAverageFront;*/
   /*lastFront = front;*/
/*}*/
