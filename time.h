#ifndef _TIME_H
#define _TIME_H

#if ARDUINO >= 100
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

class TimeClass {
  
  public:
    
    void begin();
    inline void increment();
    unsigned long micros();
//    unsigned long millis();
  
  private:  

    volatile unsigned long overflowCounter;
  
};


extern TimeClass Time;

#endif
