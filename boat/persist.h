#ifndef persist_h
#define persist_h

#define MAX_EEPROM 960

int last_value;
char data[MAX_EEPROM];

void start_writing();
void persist(double front, double top, double bottom,
             double rudderAngle, double thrust, double refSideWall);
void recall();

#endif
