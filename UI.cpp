#include "UI.h"

#define LED_BLINK_SLOW_PERIOD   500
#define LED_BLINK_FAST_PERIOD   125

void UI::ledOn() {

  if (!led_on_status) {

    // Set led to HIGH
    digitalWrite(led_pin, HIGH);

    // Set led status
    led_on_status = true;

  }

}

void UI::ledOff() {

  if (led_on_status) {

    // Set led to LOW
    digitalWrite(led_pin, LOW);

    // Set led status
    led_on_status = false;

  }

}


void UI::ledBlinkSlow() {

  // Led blink
  ledBlink(LED_BLINK_SLOW_PERIOD);

}

void UI::ledBlinkFast() {

  // Led blink
  ledBlink(LED_BLINK_FAST_PERIOD);

}

void UI::ledBlinkSlowFor(const uint32_t & duration) {

  // Led blink for
  ledBlinkFor(LED_BLINK_SLOW_PERIOD, duration);

}

void UI::ledBlinkFastFor(const uint32_t & duration) {

  // Led blink for
  ledBlinkFor(LED_BLINK_FAST_PERIOD, duration);
  
}

void UI::button(bool * pressed) {

  // Get pressed
  * pressed = digitalRead(button_pin) == HIGH;

}

void UI::waitButton() {

  bool pressed = false;

  while (!pressed) {

    // Wait 100 millis
    delay(100);

    // Update button pressed
    button(& pressed);

  }

}

void UI::init() {

  // Set motor PINs to OUTPUT
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);

  // Init led status
  led_on_status = false;

  // Set led to LOW
  digitalWrite(led_pin, LOW);

  // Init last blink millis
  last_blink_millis = 0;

}

void UI::ledBlink(const uint32_t & period) {

  // Get now
  uint32_t now = millis();

  if (now - last_blink_millis > period) {

    // Invert led PIN status
    digitalWrite(led_pin, !digitalRead(led_pin));

    // Reset last blink millis
    last_blink_millis = now;

  }

}

void UI::ledBlinkFor(const uint32_t & period, const uint32_t & duration) {

  // Get start time
  const uint32_t start = millis();
  
  // White for a byte
  while (duration == 0 || millis() - start < duration) {

    // Led blink
    ledBlink(period);

    // Just wait half period
    delay(period / 10);
    
  }
  
}

