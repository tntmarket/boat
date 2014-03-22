#ifndef persist_h
#define persist_h

#define MAX_EEPROM 960

int last_value;
unsigned char data[MAX_EEPROM];

void start_writing();
void persist(double front, double top, double bottom);
void recall();

#endif
