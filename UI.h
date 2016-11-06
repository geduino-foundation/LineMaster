#ifndef _UI_H_
#define _UI_H_

#include <Arduino.h>

class UI {

  public:

    UI(const uint8_t _led_pin, const uint8_t _button_pin) : led_pin(_led_pin), button_pin(_button_pin) {
      
      // Initialization
      init();
    
    };

    void ledOn();

    void ledOff();

    void ledBlinkSlow();

    void ledBlinkFast();

    void ledBlinkSlowFor(const uint32_t & duration);

    void ledBlinkFastFor(const uint32_t & duration);

    void button(bool * pressed);

    void waitButton();

  private:

    const uint8_t led_pin, button_pin;

    uint32_t last_blink_millis;

    bool led_on_status;

    void init();

    void ledBlink(const uint32_t & period);

    void ledBlinkFor(const uint32_t & period, const uint32_t & duration);
  
};

#endif
