#ifndef _ENCODER_HPP_
#define _ENCODER_HPP_

#include <set>
#include "EncoderSource.hpp"

namespace Encoder {

  enum Event {
    COUNTER_CLOCKWISE_STEP = 0,
    CLOCKWISE_STEP,
    BUTTON_PRESS,
    BUTTON_HOLD,
    READ_ERROR
  };

  /**
   * Event listener - reacts to events detected by the monitor. By default, all
   * events are configured to be handled by the listener, unless disabled.
   */
  class Listener() {
    public:
      virtual ~Listener() { }

      /**
       * React to the encoder event.
       * @param event the type of movement that occurred
       */
      virtual void handle(Event event) = 0;

      struct Config {
        Config() : holdThreshold(5000) { }

        /// nanoseconds to trigger button hold event
        unsigned long holdThreshold;

        /// events to ignore for the listener
        std::set<Event> disabledEvents;
      } config;
  };

  /**
   * Monitor encoder movement, notifying listeners of any events.
   */
  class Monitor() {
    public:
      Monitor(Source &source);

      virtual ~Monitor();

      /**
       * Start thread for monitoring encoder movememnt.
       * @return true if successfully started monitoring, false on error
       */
      bool start();

      /**
       * Stop monitoring.
       */
      void stop();

      /**
       * Register a listener with the monitor.
       * @param listener reference to listener
       * @return true if listener registered successfully, false otherwise
       */
      bool registerListener(Listener &listener);

    private:
      std::set<Listener*> listeners_;
  };

}
#endif
