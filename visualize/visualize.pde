import processing.serial.*;

Serial boat;

void setup() {
   boat = new Serial(this, Serial.list()[0], 9600);
   size(1200, 600);
   background(200);
}

float[] readSensors() {
   if (boat.available() > 0) {
      String msg = boat.readStringUntil('\n');
      if (msg != null) {
         return float(msg.split(" "));
      }
   }
   return (new float[] {});
}


int m;

void draw() {
   float[] values = readSensors();
   //float[] values = {170, 30, 30, 25, 255, 30};
   if(values.length >= 8) {
      background(200);
      boatDiagram(values[0], values[1], values[2], values[3], values[4], values[5]);
      graphs(values[0], values[1], values[2], values[3], values[4], values[5], values[7]);
      drawState(values[6]);
   }
}

void drawState(float state) {
   resetMatrix();
   pushStyle();
   if(state == 0) {
      fill(0, 100, 0);
   } else {
      fill(0, 0, 100);
   }
   noStroke();
   ellipse(400, 50, 50, 50);
   popStyle();
}

class Queue {
   private float[] values;
   int n;

   Queue() {
      values = new float[300];
      for(int i = 0; i < 300; i++) {
         values[i] = 0;
      }
      n = 0;
   }

   void enqueue(float value) {
      values[n] = value;
      n = (n + 1) % 300;
   }

   float justQueued() {
      int i = n - 1;
      if(i == -1) {
         return values[299];
      } else {
         return values[i];
      }
   }

   float get(int i) {
      return values[i];
   }

}

class Graph {
   Queue values;
   float x;
   float y;
   color c;

   Graph(float _x, float _y, color _c) {
      x = _x;
      y = _y;
      c = _c;
      values = new Queue();
   }

   void draw() {
      float j = 0;
      resetMatrix();
      pushMatrix();
      pushStyle();

      translate(x, y);

      line(0, 0, 600, 0); 
      line(0, 0, 0, -200); 

      noFill();
      stroke(c);
      beginShape();
      for(int i = values.n; i < 300; i++) {
         vertex(j, -values.get(i)); 
         j += 2;
      }
      for(int i = 0; i <= values.n-1; i++) {
         vertex(j, -values.get(i)); 
         j += 2;
      }
      endShape();

      popStyle();
      popMatrix();
   }

   void enqueue(float value) {
      values.enqueue(value);
   }
}

float WIDTH = 13,
      HEIGHT = 20;

Graph sideWallGraph = new Graph(550, 250, color(0));
Graph frontWallGraph = new Graph(550, 250, color(0, 0, 150));
Graph refSideWallGraph = new Graph(550, 250, color(0, 150, 0));

Graph rudderGraph = new Graph(550, 500, color(0));
Graph dFrontWallGraph = new Graph(550, 500, color(0, 0, 150));
//Graph dSideWallGraph = new Graph(550, 500, color(0));
void graphs(float front, float top, float bottom, float rudderAngle, float thrust, float refSideWall, float dFront) {
   resetMatrix();
   pushMatrix();
   pushStyle();
   float angle = atan((top-bottom)/HEIGHT);
   float sideWall = cos(angle)*top + WIDTH/2;
   sideWallGraph.enqueue(sideWall);
   frontWallGraph.enqueue(front);
   refSideWallGraph.enqueue(refSideWall);
   //dSideWallGraph.enqueue(front);
   rudderGraph.enqueue(rudderAngle);
   dFrontWallGraph.enqueue(dFront);

   sideWallGraph.draw();
   refSideWallGraph.draw();
   frontWallGraph.draw();
   //dSideWallGraph.draw();
   rudderGraph.draw();
   dFrontWallGraph.draw();
   popMatrix();
   popStyle();
}

void boatDiagram(float front, float top, float bottom, float rudderAngle, float thrust, float refSideWall) {
   resetMatrix();
   pushMatrix();
   pushStyle();
   translate(200, 0);
   stroke(0);
   strokeWeight(2);
   float angle = atan((top-bottom)/HEIGHT);
   float sideWall = cos(angle)*top + WIDTH/2;
   translate(0, 450);
   if(-sin(angle)*front < sideWall) {
      line(-200, -cos(angle)*front*2, sideWall*2, -cos(angle)*front*2); 
      line(sideWall*2, -cos(angle)*front*2, sideWall*2, 600-450); 
      line(sideWall*2, -cos(angle)*front*2, sideWall*2, 600-450); 
      stroke(0, 150, 0);
      strokeWeight(1);
      line((sideWall-refSideWall)*2, -cos(angle)*front*2, (sideWall-refSideWall)*2, 600-450); 
   } else {
      line(sideWall*2, -450, sideWall*2, 600-450); 
      stroke(0, 150, 0);
      strokeWeight(1);
      line((sideWall-refSideWall)*2, -450, (sideWall-refSideWall)*2, 600-450); 
   }
   stroke(0);
   rotate(-angle);
   boat();
   frontRay(front);
   topRay(top);
   bottomRay(bottom);
   rudder(rudderAngle);
   popStyle();
   popMatrix();
}

void boat() {
   stroke(0);
   rect(-WIDTH, 0, WIDTH*2, HEIGHT*2); 
} 
void frontRay(float front) {
   if(front >= 200) {
      stroke(255, 0, 0);
   } else {
      stroke(0);
   }
   line(0, 0, 0, -front*2); 
} 
void topRay(float top) {
   if(top >= 100) {
      stroke(255, 0, 0);
   } else {
      stroke(0);
   }
   line(WIDTH, 0, WIDTH + top*2, 0);
}
void bottomRay(float bottom) {
   if(bottom >= 100) {
      stroke(255, 0, 0);
   } else {
      stroke(0);
   }
   line(WIDTH, HEIGHT*2, WIDTH + bottom*2, HEIGHT*2);
}
void rudder(float rudderAngle) { 
   stroke(0);
   translate(0, HEIGHT*2);
   rotate(rudderAngle*PI/180);
   line(0, 0, 0, 20);
}
