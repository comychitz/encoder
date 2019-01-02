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
       * @return reading value of knob
       *         0 if knob steady in place
       *         -1 on error
       */
      virtual int getKnobReading() = 0;
  }; 

}
#endif
