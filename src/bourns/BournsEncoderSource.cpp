#include "BournsEncoderSource.hpp"

extern "C" {
#include <wiringPi.h>
}

BournsSource::BournsSource() : setup_(false) {
}

BournsSource::~BournsSource() {

}

bool BournsSource::setup(PinConfig config) {
  wiringPiSetup(); // will abort the program if fails in here
  pinMode(config.pinA, INPUT);
  pullUpDnControl(config.pinA, PUD_UP);
  pinMode(config.pinB, INPUT);
  pullUpDnControl(config.pinB, PUD_UP);
  pinMode(config.pinC, INPUT);
  pullUpDnControl(config.pinC, PUD_UP);
  config_ = config;
  setup_ = true;
  return true;
}

int BournsSource::getButtonReading() {
  int err = -1, pressed = 1, unpressed = 0;
  return !setup_ ? err : digitalRead(config_.pinC) ? unpressed : pressed;
}

int BournsSource::getKnobReading() {
  int pinAVal = digitalRead(config_.pinA);
  int pinBVal = digitalRead(config_.pinC);
  char reading = 0x00;
  if(pinAVal == 0) 
  {
    reading |= 0x02;
  }
  if(pinBVal == 0)
  {
    reading |= 0x01;
  }
  return reading;
}
