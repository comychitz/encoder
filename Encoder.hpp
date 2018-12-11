#ifndef _ENCODER_HPP_
#define _ENCODER_HPP_

#include <set>
#include <unordered_map>

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
      };
  };

  /**
   * Monitor encoder movement, notifying listeners of any events.
   */
  class Monitor() {
    public:
      Monitor();

      virtual ~Monitor();

      /**
       * Monitor the encoder movememnt - spawns thread for monitoring.
       */
      void monitor();

      /**
       * Register a listener with the monitor.
       * @param listener reference to listener
       * @param config configuration of the listener
       */
      void registerListener(Listener &listener, const Listener::Config &config);

    private:
      std::unordered_map<Listener*, Listener::Config> listeners_;
  };

}
#endif
