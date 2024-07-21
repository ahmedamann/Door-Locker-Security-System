 /******************************************************************************
 *
 * Module: buzzer
 *
 * File Name: buzzer.c
 *
 * Description: The Source File for the buzzer Driver.
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/

/*******************************************************************************
 *                              Included Files                                 *
 *******************************************************************************/
#include "buzzer.h"

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

void Buzzer_init(void)
{
    /* Configure the Buzzer pin as an output pin */
    GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
    /* Ensure the Buzzer is off at initialization */
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}

/* Turns on the Buzzer using GPIO */
void Buzzer_on(void)
{
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

/* Turns off the Buzzer using GPIO */
void Buzzer_off(void)
{
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
