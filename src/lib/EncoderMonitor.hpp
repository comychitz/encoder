#ifndef _ENCODER_HPP_
#define _ENCODER_HPP_

#include <set>
#include <mutex>
#include "EncoderSource.hpp"

namespace Encoder {

  enum Event {
    COUNTER_CLOCKWISE_STEP = 0,
    CLOCKWISE_STEP,
    BUTTON_PUSH,
    BUTTON_HOLD,
    BUTTON_RELEASE,
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

      /**
       * Unregister a listener.
       */
      void unregisterListener(Listener &listener);

    private:
      /**
       * monitor the knob activity
       */
      void monitorKnob_();

      /**
       * monitor push button activity
       */
      void monitorPush_();

      /**
       * notify all listeners of an event that occurred
       */
      void notifyListeners_(Event event);

      /**
       * notify a single listener
       */
      void notifyListener_(Listener *listener, Event event);

      bool running_;
      Source &source_;
      std::mutex notifyLock;
      std::set<Listener*> listeners_;
      std::thread knobThread_, pushThread_;
  };

}
#endif
