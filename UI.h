#ifndef _UI_H_
#define _UI_H_

#include <Arduino.h>

class UI {

  public:

    UI(const unsigned int _led_pin, const unsigned int _button_pin) : led_pin(_led_pin), button_pin(_button_pin) {
      
      // Initialization
      init();
    
    };

    void ledOn();

    void ledOff();

    void ledBlinkSlow();

    void ledBlinkFast();

    void ledBlinkSlowFor(const unsigned long & duration);

    void ledBlinkFastFor(const unsigned long & duration);

    void button(boolean * pressed);

    void waitButton();

  private:

    const unsigned int led_pin, button_pin;

    unsigned long last_blink_millis;

    boolean led_on_status;

    void init();

    void ledBlink(const unsigned long & period);

    void ledBlinkFor(const unsigned long & period, const unsigned long & duration);
  
};

#endif
