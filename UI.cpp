#include "UI.h"

#define LED_BLINK_SLOW_PERIOD   500
#define LED_BLINK_FAST_PERIOD   125

void UI::ledOn() {

  if (!ledOnStatus) {

    // Set led to HIGH
    digitalWrite(ledPin, HIGH);

    // Set led status
    ledOnStatus = true;

  }

}

void UI::ledOff() {

  if (ledOnStatus) {

    // Set led to LOW
    digitalWrite(ledPin, LOW);

    // Set led status
    ledOnStatus = false;

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

void UI::ledBlinkSlowFor(const unsigned long duration) {

  // Led blink for
  ledBlinkFor(LED_BLINK_SLOW_PERIOD, duration);

}

void UI::ledBlinkFastFor(const unsigned long duration) {

  // Led blink for
  ledBlinkFor(LED_BLINK_FAST_PERIOD, duration);
  
}

void UI::button(boolean * pressed) {

  // Get pressed
  * pressed = digitalRead(buttonPin) == HIGH;

}

void UI::waitButton() {

  boolean pressed = false;

  while (!pressed) {

    // Wait 100 millis
    delay(100);

    // Update button pressed
    button(& pressed);

  }

}

void UI::init() {

  // Set motor PINs to OUTPUT
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  // Init led status
  ledOnStatus = false;

  // Set led to LOW
  digitalWrite(ledPin, LOW);

  // Init last blink millis
  lastBlinkMillis = 0;

}

void UI::ledBlink(const unsigned long period) {

  // Get now
  unsigned long now = millis();

  if (now - lastBlinkMillis > period) {

    // Invert led PIN status
    digitalWrite(ledPin, !digitalRead(ledPin));

    // Reset last blink millis
    lastBlinkMillis = now;

  }

}

void UI::ledBlinkFor(const unsigned long period, const unsigned long duration) {

  // Get start time
  const unsigned long start = millis();
  
  // White for a byte
  while (duration == 0 || millis() - start < duration) {

    // Led blink
    ledBlink(period);

    // Just wait half period
    delay(period / 10);
    
  }
  
}

