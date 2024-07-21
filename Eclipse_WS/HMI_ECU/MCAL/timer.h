 /******************************************************************************
 *
 * Module: timer
 *
 * File Name: timer.h
 *
 * Description: The Header File for the timer Driver.
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/

#ifndef MCAL_TIMER_H_
#define MCAL_TIMER_H_

/*******************************************************************************
 *                              Included Files                                 *
 *******************************************************************************/

#include "../lib/std_types.h"

/*******************************************************************************
 *                              Definitions                                    *
 *******************************************************************************/

#define PWM_DUTY_CYCLE                          (50)
#define COMPARE_MODE_VALUE                      ( /* Write here */ )


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum {
	F_CPU_8, F_CPU_64, F_CPU_1024
}Timer_Prescaler;

typedef enum {
    NORMAL_MODE, COMPARE_MODE, PWM_MODE
}Timer_Mode;

typedef struct
{
	uint16 initial_value;
	uint16 compare_value;
	Timer_Prescaler prescaler;
	Timer_Mode mode;

} Timer_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


void Timer1_init(const Timer_ConfigType * Config_Ptr);

void Timer1_deinit(void);

void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* MCAL_TIMER_H_ */
