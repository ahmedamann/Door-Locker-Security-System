#include "keypad.h"
#include "../MCAL/gpio.h"
#include <util/delay.h>

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

uint8 KEYPAD_getPressedKey(void)
{
	uint8 col,row;
	GPIO_setupPinDirectionR(KEYPAD_FIRST_ROW_PIN_ID, KEYPAD_FIRST_ROW_PIN_ID+3, KEYPAD_ROW_PORT_ID, PIN_INPUT);
	GPIO_setupPinDirectionR(KEYPAD_FIRST_COL_PIN_ID, KEYPAD_FIRST_COL_PIN_ID+3 ,KEYPAD_COL_PORT_ID,  PIN_INPUT);

	while(1)
	{
		for(row=0 ; row<KEYPAD_NUM_ROWS ; row++) /* loop for rows */
		{
			/*
			 * Each time setup the direction for all keypad port as input pins,
			 * except this row will be output pin
			 */
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_OUTPUT);

			/* Set/Clear the row output pin */
			GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, KEYPAD_BUTTON_PRESSED);

			for(col=0 ; col<KEYPAD_NUM_COLS ; col++) /* loop for columns */
			{
				/* Check if the switch is pressed in this column */
				if(GPIO_readPin(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+col) == KEYPAD_BUTTON_PRESSED)
				{
					return KEYPAD_4x4_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col+1);
				}
			}
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_INPUT);
			_delay_ms(5); /* Add small delay to fix CPU load issue in proteus */
		}
	}
}


/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
    uint8 keypad_button;
    switch (button_number)
    {
        case 1: keypad_button = 7; break;
        case 2: keypad_button = 8; break;
        case 3: keypad_button = 9; break;
        case 4: keypad_button = '%'; break; // ASCII Code of %
        case 5: keypad_button = 4; break;
        case 6: keypad_button = 5; break;
        case 7: keypad_button = 6; break;
        case 8: keypad_button = '*'; break; /* ASCII Code of '*' */
        case 9: keypad_button = 1; break;
        case 10: keypad_button = 2; break;
        case 11: keypad_button = 3; break;
        case 12: keypad_button = '-'; break; /* ASCII Code of '-' */
        case 13: keypad_button = 13; break;  /* ASCII of Enter */
        case 14: keypad_button = 0; break;
        case 15: keypad_button = '='; break; /* ASCII Code of '=' */
        case 16: keypad_button = '+'; break; /* ASCII Code of '+' */
        default: keypad_button = button_number; break;
    }
    return keypad_button;
}
