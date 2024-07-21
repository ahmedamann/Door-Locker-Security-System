 /******************************************************************************
 *
 * Module: buzzer
 *
 * File Name: buzzer.h
 *
 * Description: The Header File for the buzzer Driver.
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/

#ifndef HAL_BUZZER_H_
#define HAL_BUZZER_H_

/*******************************************************************************
 *                              Included Files                                 *
 *******************************************************************************/

#include "../lib/std_types.h"
#include "../MCAL/gpio.h"

/*******************************************************************************
 *                      Buzzer Hardware Pin Configuration                      *
 *******************************************************************************/

#define BUZZER_PORT_ID    PORTD_ID  /* Port where the buzzer is connected */
#define BUZZER_PIN_ID     PIN7_ID   /* Pin number where the buzzer is connected */

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Initializes the Buzzer hardware */
void Buzzer_init(void);

/* Turns on the Buzzer using GPIO */
void Buzzer_on(void);

/* Turns off the Buzzer using GPIO */
void Buzzer_off(void);

#endif /* HAL_BUZZER_H_ */
