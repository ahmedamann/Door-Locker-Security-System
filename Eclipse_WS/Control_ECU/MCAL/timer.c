 /******************************************************************************
 *
 * Module: timer
 *
 * File Name: timer.c
 *
 * Description: The Source File for the timer Driver.
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/

/*******************************************************************************
 *                              Included Files                                 *
 *******************************************************************************/

#include <avr/io.h>            /* For the use of Registers Names for configuration */
#include <avr/interrupt.h>     /* For the use of ISRs */

#include "../lib/std_types.h"  /* For the use of NULL_PTR */
#include "timer.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                        Interrupt Service Routine (ISR)                      *
 *******************************************************************************/

ISR(TIMER1_COMPA_vect)
{
    if (g_callBackPtr != NULL_PTR)
    {
        (*g_callBackPtr)();
    }
}

/*******************************************************************************
 *                              Functions Definitions                           *
 *******************************************************************************/

void Timer1_setCallBack(void(*a_ptr)(void))
{
	 g_callBackPtr = a_ptr;
}

void Timer1_init(const Timer_ConfigType * Config_Ptr)
{
    /* Clear Timer control registers */
    TCCR1A = 0;
    TCCR1B = 0;

    /* Set Timer initial value */
    TCNT1 = Config_Ptr->initial_value;

    /* Switch statement for the pre-scaler configuration */
    switch (Config_Ptr->prescaler) {
        case F_CPU_8:
            TCCR1B |= (1 << CS11);
            break;
        case F_CPU_64:
            TCCR1B |= (1 << CS11) | (1 << CS10);
            break;
        case F_CPU_1024:
            TCCR1B |= (1 << CS12) | (1 << CS10);
            break;
        default:
            break;
    }

    /* Switch statement for setting the correct callback function for different modes */
    switch (Config_Ptr->mode) {
        case PWM_MODE:
            TIMSK |= (1 << OCIE1A);    // Enable Output Compare A Match Interrupt
            TCCR1A |= (1 << WGM11) | (1 << COM1A1); // Configure for Fast PWM mode, non-inverted
            TCCR1B |= (1 << WGM12) | (1 << WGM13);  // Configure for Fast PWM mode
            OCR1A = Config_Ptr->compare_value;      // Set the duty cycle
            break;
        case NORMAL_MODE:
            TIMSK |= (1 << TOIE1);     // Enable Overflow Interrupt
            TCCR1A = 0;                // Normal mode
            break;
        case COMPARE_MODE:
            TIMSK |= (1 << OCIE1A);    // Enable Output Compare A Match Interrupt
            TCCR1A = 0;                // Clear Timer on Compare Match (CTC) mode
            TCCR1B |= (1 << WGM12);    // CTC mode
            OCR1A = Config_Ptr->compare_value;      // Set the compare value
            break;
        default:
            break;
    }
}

void Timer1_deinit(void)
{
	TCNT1 = 0;
	TCCR1B = 0;
}
