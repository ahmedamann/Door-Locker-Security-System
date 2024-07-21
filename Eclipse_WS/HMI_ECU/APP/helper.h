 /******************************************************************************
 *
 * Module: helper
 *
 * File Name: helper.h
 *
 * Description: The Header File for the helper Driver.
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/

#ifndef APP_HELPER_H_
#define APP_HELPER_H_

/*******************************************************************************
 *                              Included Files                                 *
 *******************************************************************************/
#include "../lib/std_types.h"

/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/
#define COMPARE_VALUE                   (7812)
#define PASSWORD_LENGTH_BYTES           (2)

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
	MAIN, REGISTER, LOGIN_CHANGE_PASS, LOGIN_DOOR_OPEN
}statusType;

/*******************************************************************************
 *                               CODES FOR COMMUNICATION                       *
 *******************************************************************************/

#define CODE_OPEN_DOOR                  (0x01)
#define CODE_SAVE_PASSWORD              (0x02)
#define CODE_RETREIVE_PASSWORD          (0x03)
#define CODE_ACTIVATE_BUZZER            (0x04)

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void APP_registerMenu(void);
void APP_loginMenu(void);
void APP_mainMenu(void);

uint8 APP_checkPassword (uint8 password);
void APP_keypadToVariable(uint8* variable);

void APP_deinit_passwords(void);

void Timer_countTicks(void);
void Timer_delaySeconds(uint16 seconds);

#endif /* APP_HELPER_H_ */
