#include "UI.h"

#define LED_BLINK_SLOW_PERIOD   1000
#define LED_BLINK_FAST_PERIOD   250

void UI::ledOn() {

  // Set led to HIGH
  digitalWrite(ledPin, HIGH);
  
}

void UI::ledOff() {

  // Set led to LOW
  digitalWrite(ledPin, LOW);
  
}


void UI::ledBlinkSlow() {

  // Led blink
  ledBlink(LED_BLINK_SLOW_PERIOD);
  
}

void UI::ledBlinkFast() {

  // Led blink
  ledBlink(LED_BLINK_FAST_PERIOD);
  
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

  // Turn led off
  ledOff();

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

