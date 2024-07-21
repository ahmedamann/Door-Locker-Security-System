/*
 *  File: lcd.c
 *
 *  Created on: Jun 6, 2024
 *  Author: Ahmed Aman
 */

#include "lcd.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * Initializes the LCD module:
 * 1. Configures the direction of RS and E pins as output.
 * 2. Sets the data mode to 8-bits.
 * 3. Performs necessary initialization delays.
 */
void LCD_init(void)
{
    /* Configure RS and E pins as output */
    GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);

    /* Configure data port as output */
    GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);

    _delay_ms(20);  /* Delay for LCD power-on (must be > 15ms) */

    /* Initialize LCD settings */
    LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE); /* 2-line display, 8-bit data */
    LCD_sendCommand(LCD_CURSOR_OFF); /* Turn off cursor */
    LCD_sendCommand(LCD_CLEAR_COMMAND); /* Clear LCD screen */
}

/*
 * Description:
 * Sends a command to the LCD module.
 *
 * Parameters:
 * - command: Command byte to be sent to the LCD.
 */
void LCD_sendCommand(uint8 command)
{
    GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW); /* Instruction Mode RS=0 */
    _delay_ms(1); /* Delay for processing (Tas = 50ns) */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH); /* Enable LCD E=1 */
    _delay_ms(1); /* Delay for processing (Tpw - Tdws = 190ns) */
    GPIO_writePort(LCD_DATA_PORT_ID, command); /* Output command to data bus (D0 --> D7) */
    _delay_ms(1); /* Delay for processing (Tdsw = 100ns) */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW); /* Disable LCD E=0 */
    _delay_ms(1); /* Delay for processing (Th = 13ns) */
}

/*
 * Description:
 * Displays a character on the LCD screen.
 *
 * Parameters:
 * - data: Character to be displayed.
 */
void LCD_displayCharacter(uint8 data)
{
    GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH); /* Data Mode RS=1 */
    _delay_ms(1); /* Delay for processing (Tas = 50ns) */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH); /* Enable LCD E=1 */
    _delay_ms(1); /* Delay for processing (Tpw - Tdws = 190ns) */
    GPIO_writePort(LCD_DATA_PORT_ID, data); /* Output data to data bus (D0 --> D7) */
    _delay_ms(1); /* Delay for processing (Tdsw = 100ns) */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW); /* Disable LCD E=0 */
    _delay_ms(1); /* Delay for processing (Th = 13ns) */
}

/*
 * Description:
 * Displays a string of characters on the LCD screen.
 *
 * Parameters:
 * - Str: Pointer to the string to be displayed.
 */
void LCD_displayString(const char *Str)
{
    uint8 i = 0;
    while (Str[i] != '\0')
    {
        LCD_displayCharacter(Str[i]);
        i++;
    }
}

/*
 * Description:
 * Moves the cursor to a specified row and column on the LCD screen.
 *
 * Parameters:
 * - row: Row index (0 to 1 for a 2-line display).
 * - col: Column index (0 to 15 for a 16-column display).
 */
void LCD_moveCursor(uint8 row, uint8 col)
{
    uint8 lcd_memory_address;

    switch(row)
    {
        case 0:
            lcd_memory_address = col;
            break;
        case 1:
            lcd_memory_address = col + 0x40;
            break;
        /* Add cases for additional rows if needed */
    }

    LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description:
 * Displays a string of characters starting at a specified row and column on the LCD screen.
 *
 * Parameters:
 * - row: Row index (0 to 1 for a 2-line display).
 * - col: Column index (0 to 15 for a 16-column display).
 * - Str: Pointer to the string to be displayed.
 */
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *Str)
{
    LCD_moveCursor(row, col); /* Move cursor to specified position */
    LCD_displayString(Str); /* Display the string */
}

/*
 * Description:
 * Converts an integer to a string and displays it on the LCD screen.
 *
 * Parameters:
 * - data: Integer value to be converted and displayed.
 */
void LCD_integerToString(int data)
{
	char buff[20]; /* String to hold the ascii result */
	itoa(data,buff,10);
	LCD_displayString(buff); /* Display the string */
}
/*
 * Description:
 * Clears the LCD screen by sending the clear display command.
 */
void LCD_clearScreen(void)
{
    LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}

void LCD_enterKeyMessage (const char* key)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString(key);
	LCD_moveCursor(1,0);
}
