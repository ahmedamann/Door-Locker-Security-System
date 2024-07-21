/*
 *  File: pwm.h
 *
 *  Created on: Jun 6, 2024
 *  Author: Ahmed Aman
 */

#ifndef MCAL_PWM_H_
#define MCAL_PWM_H_

#include "../LIB/avr_registers_types.h"
#include "../LIB/std_types.h"
#include "../LIB/common_macros.h"

#include "../MCAL/gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PWM_OC0_PORT    PORTB_ID
#define PWM_OC0_PIN     3

/*******************************************************************************
 *                               Type Definitions			                   *
 *******************************************************************************/

typedef enum{
	NO_CLOCK, NO_PRESCALER, F_CPU8, F_CPU64, F_CPU256, F_CPU1024
}PWM_Prescaler;


/*******************************************************************************
 *                              Macros for Timer 0 (PWM mode)                  *
 *******************************************************************************/

/* Set Timer 0 to Fast PWM mode, non-inverted */
#define TIMER0_FAST_PWM_MODE          				(TCCR0.byte |= (1 << 6) | (1 << 5) | (1 << 3))

/* Set Timer 0 to Fast PWM mode with non-inverted output */
#define TIMER0_START_FROM(value)      				(TCNT0.byte = value)

/* Stop Timer 0 */
#define TIMER0_STOP                   				(TCCR0.byte &= ~((1<<CS02) | (1<<CS01) | (1<<CS00)))

/* Set PWM duty cycle for Timer 0 (0-100%) */
#define TIMER0_SET_DUTY_CYCLE(duty)   				(OCR0.byte = (((uint16)(duty * 255)) / 100))

/* Set Timer 0 Prescaler */
#define TIMER0_PRESCALER(prescaler)                 (TCCR0.byte |= (0x07 & prescaler))


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * The initializer function for the PWM
 */
void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* MCAL_PWM_H_ */
