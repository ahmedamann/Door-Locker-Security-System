 /******************************************************************************
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
 *                              Definitions                                    *
 *******************************************************************************/
#define EEPROM_PASSWORD_LOCATION        (0x00)

#define EEPROM_ADDRESS                  (0b00000010)
#define COMPARE_VALUE                   (7812)

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

void APP_openDoorHandler(void);
void APP_savePassword(void);
void APP_sendPassword(void);
void APP_activateBuzzer(void);
void Timer_delaySeconds(uint16 seconds);
void Timer_countTicks(void);


#endif /* APP_HELPER_H_ */
