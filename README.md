## encoder.h
A small set of C functions targeted for iterfacing a rotary encoder (specifically, Bourns Pro Audio Incremental Encoder PEC11-4215F-S24) with a Raspberry Pi B+ V1.2.

### usage
Include "encoder.h" in your C/C++ program and link with the encoder object file. Begin reading values from the encoder by calling startMonitoring(). Use stopMonitoring() to stop reading and wait() if you are looking to stop and wait in your program.

defined event types:
  - CLOCKWISE_STEP
  - COUNTER_CLOCKWISE_STEP
  - PUSHED
  - PUSHED_AND_HELD

to set the gpio pins to read the data from the encoder on the pi use the integer globals PIN_A, PIN_B, PIN_C. see the image here (https://github.com/comychitz/encoder/blob/master/encoder_gpio_pin_out.png) for the pin out.

##### dependencies
1. wiringPi 
2. pthread

### todo
nothing in the todo queue currently.

#### example usage (using C)
```C
#include "encoder.h"
#include <stdio.h>

// the gpio pins to use
int gpio1 = 7,
    gpio2 = 0,
    gpio3 = 2;

int main( )
{
  char reading;
  int value = 0;

  setup( gpio1, gpio2, gpio3 );    
  startReading();

  while( 1 ) 
  {

    reading = getReading();

    /* ["critical section start"] */
    if( reading == CLOCKWISE_STEP )
    {
      value++;
    }   
    else if( reading == COUNTER_CLOCKWISE_STEP )
    {
      value--;
    }   
    else if( reading == PUSHED )
    {
      value = 0;
    } 
    else if( reading == PUSHED_AND_HELD )
    {
      value = 100;
    }
    printf( "%d\n", value );
    /* ["critical section end"] */

    continueReading(); 
  }

  stopReading();

  return 0;
}
```
