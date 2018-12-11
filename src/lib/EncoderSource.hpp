#ifndef _ENCODER_SOURCE_HPP_
#define _ENCODER_SOURCE_HPP_

namespace Encoder {

  /**
   * Encoder source interface - responsible for providing reading from an encoder
   * that has a knob and button
   */
  class Source {
    public:
      virtual ~Source() { }

      /**
       * check if the encoder is being pressed
       * @return 1 if pressed
       *         0 if unpressed
       *         -1 on error
       */
      virtual int getButtonReading() = 0;

      /**
       * get knob reading
       * @return 1 if counter clockwise turn
       *         0 if clockwise turn
       *         -1 on error
       */
      virtual int getKnobReading() = 0;
  };
 
  /**
   * Encoder source for reading from Bourns Pro Audio Incremental Encoder 
   * PEC11-4215F-S24.
   */
  class BournsSource : public Source {
    public:
      Source();

      virtual ~Source();

      struct PinConfig {
        int pinA;
        int pinB;
        int pinC;
      };

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

}
#endif
