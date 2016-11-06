#ifndef _TYPES_H_
#define _TYPES_H_

struct __attribute__((packed)) Setup {
    unsigned int pid_proportional;
    unsigned int pid_integrative;
    unsigned int pid_derivative;
    unsigned int motors_max_speed;
    unsigned int ir_in_line_threshold;
    unsigned int ir_noise_threshold;
    unsigned int telemetry_enabled;
};

struct __attribute__((packed)) TelemetryData {
    unsigned long time;
    int error;
};

#endif
