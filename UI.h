#ifndef _UI_H_
#define _UI_H_

#include <Arduino.h>

class UI {

  public:

    UI(const unsigned int _ledPin, const unsigned int _buttonPin) : ledPin(_ledPin), buttonPin(_buttonPin) {
      
      // Initialization
      init();
    
    };

    void ledOn();

    void ledOff();

    void ledBlinkSlow();

    void ledBlinkFast();

    void ledBlinkSlowFor(const unsigned long duration);

    void ledBlinkFastFor(const unsigned long duration);

    void button(boolean * pressed);

    void waitButton();

  private:

    const unsigned int ledPin, buttonPin;

    unsigned long lastBlinkMillis;

    boolean ledOnStatus;

    void init();

    void ledBlink(const unsigned long period);

    void ledBlinkFor(const unsigned long period, const unsigned long duration);
  
};

#endif
