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
