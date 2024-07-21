 /******************************************************************************
 *
 * Module: dc_motor
 *
 * File Name: dc_motor.c
 *
 * Description: The Source File for the dc_motor Driver.
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/

/*******************************************************************************
 *                              Included Files                                 *
 *******************************************************************************/

#include "dc_motor.h"
#include "../MCAL/gpio.h"
#include "../MCAL/pwm.h"

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

void DCMotor_Init(void)
{
	/* Setup Direction for IN1 and IN2 to be Output pins */
	GPIO_setupPinDirection(DC_MOTOR_H_BRIDGE_IN1_PORT,DC_MOTOR_H_BRIDGE_IN1_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_H_BRIDGE_IN2_PORT,DC_MOTOR_H_BRIDGE_IN2_PIN,PIN_OUTPUT);

	/* Stop the Motor initially */
	GPIO_writePin(DC_MOTOR_H_BRIDGE_IN1_PORT,DC_MOTOR_H_BRIDGE_IN1_PIN,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_H_BRIDGE_IN2_PORT,DC_MOTOR_H_BRIDGE_IN2_PIN,LOGIC_LOW);
}



/*Setup the direction of rotation of the motor*/
void DCMotor_Rotate(MOTOR_STATE state)
{

	switch(state)
	{
		case STOP:
			GPIO_writePin(DC_MOTOR_H_BRIDGE_IN1_PORT,DC_MOTOR_H_BRIDGE_IN1_PIN,LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_H_BRIDGE_IN2_PORT,DC_MOTOR_H_BRIDGE_IN2_PIN,LOGIC_LOW);
			break;
		case CW:
			GPIO_writePin(DC_MOTOR_H_BRIDGE_IN1_PORT,DC_MOTOR_H_BRIDGE_IN1_PIN,LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_H_BRIDGE_IN2_PORT,DC_MOTOR_H_BRIDGE_IN2_PIN,LOGIC_HIGH);
			break;
		case ACW:
			GPIO_writePin(DC_MOTOR_H_BRIDGE_IN1_PORT,DC_MOTOR_H_BRIDGE_IN1_PIN,LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR_H_BRIDGE_IN2_PORT,DC_MOTOR_H_BRIDGE_IN2_PIN,LOGIC_LOW);
			break;
	}


	PWM_Timer0_Start(100);
}
