#include "EncoderMonitor.hpp"
#include <unistd.h>
#include <thread>

namespace Encoder {

  Monitor::Monitor(Source &source) 
    : running_(false), source_(source), knobThread_{}, pushThread_{} {
  }

  Monitor::~Monitor() {
  }

  bool Monitor::start() {
    if (running_) {
      return false;
    }
    running_ = true;
    knobThread_ = std::thread{&Monitor::monitorKnob_, this};
    pushThread_ = std::thread{&Monitor::monitorPush_, this};
    return true;
  }

  void Monitor::stop() {
    running_ = false;
    knobThread_.join();
    pushThread_.join();
  }

  bool Monitor::registerListener(Listener &listener) {
    if (listeners_.find(&listener) != listeners_.end()) {
      return false;
    }
    listeners_.insert(&listener);
    return true;
  }

  void Monitor::unregisterListener(Listener &listener) {
    listeners_.erase(&listener);
  }

  void Monitor::monitorKnob_() {
    while (running_) 
    {
      char reading1 = source_.getKnobReading(0x00);
      if (reading1 == 0x00)
      {
        continue;
      }
      char reading2 = source_.getKnobReading(reading1);
      if (reading2 == 0x03)
      {
        char reading3 = source_.getKnobReading(reading2);
        if (reading2 - reading3 == 2 && reading1 == 2)
        {
          notifyListeners_(CLOCKWISE_STEP);
        } 
        else
        {
          notifyListeners_(COUNTER_CLOCKWISE_STEP);
        }
      }
    }
  }

  void Monitor::monitorPush_() {
    while (running_)
    {
      unsigned long timeHeldDown = 0;
      while (getPushButtonReading())
      {
        std::set<Listener*> listeners;
        if(timeHeldDown == 0) {
          listeners = listeners_;
          notifyListeners_(BUTTON_PUSH);
        }
        for (auto &listener : listeners) {
          if (listener.config.disabledEvents.find(BUTTON_HOLD) == 
              listener.config.disabledEvents.end() && 
              listener.config.holdThreshold <= timeHeldDown) {
            notifyListener_(listener, BUTTON_HOLD);
            listeners.erase(listener);
          }
        }
        timeHeldDown++;
        usleep(1000*1);
      }
      notifyListeners(BUTTON_RELEASE);
      usleep(1000*10);
    }
  }

  void Monitor::notifyListeners_(Event event) {
    for (auto &listener : listeners_) {
      notifyListener_(listener, event);
    }
  }

  void Monitor::notifyListener_(Listener *listener, Event event) {
    notifyLock.lock();
    listener->handle(event);
    notifyLock.unlock();
  }
}
