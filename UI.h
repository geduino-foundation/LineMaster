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

    void button(boolean * pressed);

    void waitButton();

  private:

    const unsigned int ledPin, buttonPin;

    unsigned long lastBlinkMillis;

    void init();

    void ledBlink(const unsigned long period);
  
};

#endif
