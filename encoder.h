#ifndef ENCODER_H
#define ENCODER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <wiringPi.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE	      256

/* Definitions for each encoder action */
#define NO_ACTION 		    ( (const char) 0x00 )
#define CLOCKWISE_STEP		    ( (const char) 0x01 )
#define COUNTER_CLOCKWISE_STEP	    ( (const char) 0x02 )
#define PUSHED			    ( (const char) 0x03 )
#define PUSHED_AND_HELD		    ( (const char) 0x04 )

// function delcarations for main API
bool setup( int pinA, int pinB, int pinC);
void clearBuffer( void );
bool enableBuffering( void );
bool disableBuffering( void );
void setHoldTime( long long holdTime );
bool startReading( void );
void stopReading( void );
char getReading( void );
void continueReading( void );

// (private) globals, unfortunately
pthread_t rotateThread, pushThread;
bool bufferingEnabled;
sem_t produced, consumed;
pthread_mutex_t bufferLock;

// (private) function declarations
void add_to_buffer( char value );
void monitorRotation( void * );
void monitorPushButton( void * );
bool getPushButtonReading( void );
char getKnobReading( char prev );

#endif /* ENCODER_H */
