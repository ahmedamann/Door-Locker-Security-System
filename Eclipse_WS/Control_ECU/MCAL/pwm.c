/*
 *  File: pwm.c
 *
 *  Created on: Jun 6, 2024
 *  Author: Ahmed Aman
 */
#include "pwm.h"

PWM_Prescaler prescaler = F_CPU8;

void PWM_Timer0_Start(uint8 duty_cycle)
{
    /* Start Timer 0 counting from 0 */
    TIMER0_START_FROM(0);

    /* Set the PWM duty cycle by calculating the value for the OCR0 register
       (duty_cycle is provided as a percentage, so it's scaled to 0-255) */
    TIMER0_SET_DUTY_CYCLE(duty_cycle);

    /* Set the direction of the PWM output pin (OC0) to output */
    GPIO_setupPinDirection(PWM_OC0_PORT, PWM_OC0_PIN, PIN_OUTPUT);

    /* Configure Timer 0 for Fast PWM mode with non-inverted output */
    TIMER0_FAST_PWM_MODE;

    /* Start Timer 0 with a prescaler of 8 */
    TIMER0_PRESCALER(prescaler);
}
