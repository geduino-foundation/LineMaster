/*
  types.h
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

#ifndef _TYPES_H_
#define _TYPES_H_

#ifndef ARDUINO

// Needed for types if is not Arduino
#include <stdint.h>

#endif

struct __attribute__((packed)) Setup {
    uint16_t pid_proportional;
    uint16_t pid_integrative;
    uint16_t pid_derivative;
    uint16_t pid_max_proportional;
    uint16_t pid_max_integrative;
    uint16_t pid_max_derivative; 
    uint16_t pid_max_correction;
    uint16_t motors_max_speed;
    uint16_t ir_in_line_threshold;
    uint16_t ir_noise_threshold;
    uint16_t telemetry_enabled;
};

struct __attribute__((packed)) TelemetryData {
    uint32_t time;
    int16_t error;
};

#endif
