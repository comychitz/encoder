#ifndef __BOURNS_ENCODER_SOURCE_HPP_
#define __BOURNS_ENCODER_SOURCE_HPP_

#include "EncoderSource.hpp"

/**
 * Encoder source for reading from Bourns Pro Audio Incremental Encoder 
 * PEC11-4215F-S24.
 */
class BournsSource : public Encoder::Source {
  public:
    struct PinConfig {
      int pinA;
      int pinB;
      int pinC;
    };

    BournsSource();

    virtual ~BournsSource(); 

    /**
     * perform initial setup for reading input from encoder
     * NOTE: will abort program if criticl setup error occurs
     * @param config the pin configuration
     * @return true on successful setup, false on error
     */
    bool setup(PinConfig config);

    /**
     * check if the encoder is being pressed 
     * @return 1 if pressed
     *         0 if unpressed
     *         -1 on error
     */
    int getButtonReading();

    /**
     * get knob reading 
     * @return reading value of knob
     *         0 if knob steady in place
     *         -1 on error
     */
    int getKnobReading();

  private:
    bool setup_;
    PinConfig config_;
};
