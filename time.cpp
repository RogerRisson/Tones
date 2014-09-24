
#if ARDUINO >= 100
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif


#include "time.h"

TimeClass Time;

  ISR(TIMER1_OVF_vect) {
    Time.increment();
  }

inline void TimeClass::increment(){
    overflowCounter++;
}


void TimeClass::begin() {
    // Adjust Timer 1:
    TCCR1A = B00000000;
    TCCR1B = B00000010;
    TCCR1C = B00000000;
    TIMSK1 = B00000001;
  
  
  // Redefine Timer 0 to their original values:
    TIMSK0 = 0;
    TIFR0 = 0;
    TCCR0A = 0;
    TCCR0B = 0;
    TCNT0 = 0;
    OCR0A = 0;
    OCR0B = 0;
  }


  unsigned long TimeClass::micros() {
  noInterrupts();
  unsigned int timer_save = TCNT1;
  boolean flag_interrupt = bitRead(TIFR1, 0);
  if( flag_interrupt )
  {
      timer_save = TCNT1;
      overflowCounter++;
      TIFR1 |= 0b00000001;
  }
  unsigned long ret = (overflowCounter * 65536 + timer_save) >> 1;
  interrupts();
  return ret;
  }


