 /******************************************************************************
 *
 * Module: dc_motor
 *
 * File Name: dc_motor.h
 *
 * Description: The Header File for the dc_motor Driver.
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/

#ifndef HAL_DC_MOTOR_H_
#define HAL_DC_MOTOR_H_

/*******************************************************************************
 *                              Included Files                                 *
 *******************************************************************************/

#include "../MCAL/gpio.h"
#include "../MCAL/timer.h"
#include "../lib/std_types.h"


/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/

#define DC_MOTOR_H_BRIDGE_IN1_PORT     PORTB_ID
#define DC_MOTOR_H_BRIDGE_IN2_PORT     PORTB_ID

#define DC_MOTOR_H_BRIDGE_IN1_PIN      PIN0_ID
#define DC_MOTOR_H_BRIDGE_IN2_PIN      PIN1_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*Types Declarations*/
typedef enum
{
	STOP, CW, ACW
}MOTOR_STATE;

/*Functions Prototype*/

/*Initialization of the DC Motor*/
void DCMotor_Init(void);

/*Setup the direction of rotation of the motor*/
void DCMotor_Rotate(MOTOR_STATE state);

#endif /* HAL_DC_MOTOR_H_ */
