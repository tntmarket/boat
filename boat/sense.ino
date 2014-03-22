#include "sense.h"
#include "hardware.h"


enum ToSense {
   TOP,
   FRONT_SIDE 
};

ToSense nextSense = FRONT_SIDE;

void sense(double *frontWall, double *sideWall, double *angle) {
   static unsigned int t = millis();
   static double LENGTH = 15;
   static double a = 1;
   
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
   }
}

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
