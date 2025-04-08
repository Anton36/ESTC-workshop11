#ifndef PWM_HANDLER_H
#define PWM_HANDLER_H

#include "nrfx_pwm.h"
#include "led_handler.h"
#include "nrf_gpio.h"
#include <stdint.h>
#define PWM_TOP_VALUE 255
#define PWM_MIN_VALUE 0
#define PWM_TIMER_DELAY 30


extern int i_leds;

void pwm_init(void);
void pwm_set_duty_cycle(int channel, int duty_cycle);
void pwm_playback(void);


#endif