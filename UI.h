/*
  UI.h
  Copyright (C) 2016 Alessandro Francescon

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _UI_H_
#define _UI_H_

#include <Arduino.h>

class UI {

  public:

    UI(const unsigned int _ledPin, const unsigned int _buttonPin) : ledPin(_ledPin), buttonPin(_buttonPin) {
      
      // Initialization
      init();
    
    }

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
