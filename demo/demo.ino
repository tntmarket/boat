#include <Servo.h>

#define THRUST_PIN 3
void setThrust(int thrust) {
   analogWrite(THRUST_PIN, thrust);
}

#define RUDDER_PIN 9
Servo rudder;
void setRudder(int angle) {
   rudder.write(98 - angle);
}

void setup() {
   pinMode(RUDDER_PIN, OUTPUT);
   rudder.attach(RUDDER_PIN);

   pinMode(THRUST_PIN, OUTPUT);

   setThrust(0);
   setRudder(0);

   /*Serial.begin(9600);*/
}

int thrust = 30,
    rudderAngle = -15;

unsigned int t = millis();

int da = 1;
void loop() {

   if(millis() - t < 10) {
      return;
   }
   t = millis();

   rudderAngle += da;
   if(abs(rudderAngle) >= 15) {
      da = -1*da;
   }

   setThrust(40);
   setRudder(rudderAngle);
}
