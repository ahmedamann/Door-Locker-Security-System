 /******************************************************************************
 *
 * Module: app
 *
 * File Name: app.c
 *
 * Description: The Source File for the Application.
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/
#include <avr/interrupt.h>

#include "../lib/std_types.h"
#include "../HAL/keypad.h"
#include "../HAL/lcd.h"
#include "../MCAL/uart.h"
#include "../MCAL/timer.h"
#include "helper.h"

uint8 volatile ticks = 0;  /* Global volatile variable to count timer ticks */

bool g_passwordIsSet = False;  /* Flag to indicate if the password has been set */

uint8 g_new_password = 0;        /* Variable to store the new password during creation for comparison */
uint8 g_confirm_password = 0;    /* Variable to store the confirmation password during creation for comparison */
uint8 g_input_password = 0;      /* Variable to store the input password when attempting to open the door for comparison */

uint8 g_semph = 3; /* Counting semaphore to track password attempts */

statusType g_status = REGISTER;  /* Variable to store the current status, initialized to REGISTER */

Timer_ConfigType timer_config = {
    .initial_value = 0,                /* Initial value for the timer */
    .compare_value = COMPARE_VALUE,    /* Value for the timer to compare against */
    .prescaler = F_CPU_1024,           /* Pre-scaler value for the timer clock */
    .mode = COMPARE_MODE               /* Mode of operation for the timer */
};

int main (void)
{
    /* Enable global interrupts */
    sei();

    /* UART Configurations
     * Baud Rate: 9600 bps
     * Data size: Eight bit data
     * Error Checking: Even Parity
     * Stop bits: one
     */

    /* Set the timer callback function */
    Timer1_setCallBack(Timer_countTicks);

    /* Initialize UART with the specified configurations */
    UART_ConfigType uart_config = {BAUD_RATE_9600, EIGHT_BITS, EVEN, ONE_BIT};
    UART_init(&uart_config);

    /* Initialize the LCD to start displaying */
    LCD_init();

    while(1)
    {
        /* Check the system status and call appropriate menu functions */
        if (g_status == REGISTER || g_passwordIsSet == False)
        {
            /* Call the registration menu if status is REGISTER or no password is set */
            APP_registerMenu();
        }
        else if (g_status == MAIN)
        {
            /* Call the main menu if status is MAIN */
            APP_mainMenu();
        }
        else if (g_status == LOGIN_CHANGE_PASS || g_status == LOGIN_DOOR_OPEN)
        {
            /* Call the login menu if status is LOGIN_CHANGE_PASS or LOGIN_DOOR_OPEN */
            APP_loginMenu();
        }
    }
}

/* Function to handle the login menu */
void APP_loginMenu(void)
{
    g_input_password = 0;

    while (1)
    {
        /* Check the login status */
        if (g_status != LOGIN_CHANGE_PASS && g_status != LOGIN_DOOR_OPEN)
        {
            break;
        }
        else
        {
            /* Prompt user to enter password */
            LCD_enterKeyMessage("Enter Password: ");

            /* Get the password from the keypad */
            APP_keypadToVariable(&g_input_password);

            /* Check if the entered password is correct */
            if (APP_checkPassword(g_input_password))
            {
                g_semph = 3;

                if (g_status == LOGIN_CHANGE_PASS)
                {
                    /* Change status to register if changing password */
                    g_status = REGISTER;
                }
                else if (g_status == LOGIN_DOOR_OPEN)
                {
                    /* Send command to open the door */
                    UART_sendByte(CODE_OPEN_DOOR);

                    /* Display door unlocking message */
                    LCD_clearScreen();
                    LCD_displayStringRowColumn(0, 0, "Door unlocking");
                    Timer_delaySeconds(15);

                    /* Display door open message */
                    LCD_clearScreen();
                    LCD_displayStringRowColumn(0, 0, "Door open");
                    Timer_delaySeconds(3);

                    /* Display door locking message */
                    LCD_clearScreen();
                    LCD_displayStringRowColumn(0, 0, "Door locking");
                    Timer_delaySeconds(15);

                    /* Change status to main */
                    g_status = MAIN;
                }
                break;
            }
            else
            {
                /* Decrement semaphore count */
                g_semph--;

                if (g_semph == 0)
                {
                    /* Lock the system for 60 seconds if attempts exhausted */
                    LCD_clearScreen();
                    LCD_displayStringRowColumn(0, 0, "LOCKED FOR");
                    LCD_displayStringRowColumn(1, 0, "60 SECONDS");

                    UART_sendByte(CODE_ACTIVATE_BUZZER);
                    Timer_delaySeconds(60);
                    g_semph = 3;

                    g_status = MAIN;
                }
                else
                {
                    /* Display wrong password message and remaining attempts */
                    LCD_clearScreen();
                    LCD_displayStringRowColumn(0, 0, "Wrong Password");
                    LCD_moveCursor(1, 0);
                    LCD_integerToString(g_semph);
                    LCD_displayString(" tries left");

                    Timer_delaySeconds(1);
                    break;
                }
            }
        }
    }
}


void APP_registerMenu(void)
{
    APP_deinit_passwords();  /* Clear any previously set passwords */
    while (1)
    {
        if (g_status != REGISTER)  /* Exit the loop if the status is not REGISTER */
        {
            break;
        }
        else
        {
            if (g_new_password == 0)  /* Prompt for new password if not already set */
            {
                LCD_enterKeyMessage("New Password: ");
                APP_keypadToVariable(&g_new_password);  /* Store the new password */

                LCD_enterKeyMessage("Confirm: ");
                APP_keypadToVariable(&g_confirm_password);  /* Store the confirmation password */
            }

            if (g_new_password != g_confirm_password)  /* Check if the new password matches the confirmation password */
            {
                LCD_clearScreen();
                LCD_displayStringRowColumn(0, 0, "No Match");  /* Display message for no match */
                LCD_displayStringRowColumn(1, 0, "Try again...");
                Timer_delaySeconds(1);  /* Delay for user to read the message */

                break;
            }
            else
            {
                g_passwordIsSet = True;  /* Set the flag indicating the password has been set */

                UART_sendByte(CODE_SAVE_PASSWORD);  /* Send save password code via UART */
                UART_sendByte(g_new_password);  /* Send the new password via UART */

                g_status = MAIN;  /* Update the status to MAIN */
                break;
            }
        }
    }
}

/* Function to handle the main menu */
void APP_mainMenu(void)
{
    {
        uint8 key;

        /* Clear the LCD and display main menu options */
        LCD_clearScreen();
        LCD_displayStringRowColumn(0, 0, "+ : Open Door");
        LCD_displayStringRowColumn(1, 0, "- : Change Pass");

        while (1)
        {
            /* Check if the status has changed */
            if (g_status != MAIN)
            {
                break;
            }
            else
            {
                /* Get the pressed key from the keypad */
                key = KEYPAD_getPressedKey();
                _delay_ms(200);

                if (key == '+')
                {
                    /* Change status to LOGIN_DOOR_OPEN if '+' key is pressed */
                    g_status = LOGIN_DOOR_OPEN;
                    break;
                }
                else if (key == '-')
                {
                    /* Change status to LOGIN_CHANGE_PASS if '-' key is pressed */
                    g_status = LOGIN_CHANGE_PASS;
                    break;
                }
                else
                {
                    /* Do nothing if any other key is pressed */
                }
            }
        }
    }
}

uint8 APP_checkPassword(uint8 password)
{
    uint8 retrieved_password;

    /* Request the password retrieval from the UART */
    UART_sendByte(CODE_RETREIVE_PASSWORD);

    /* Receive the retrieved password via UART */
    retrieved_password = UART_receiveByte();

    /* Check if the retrieved password matches the provided password */
    if (retrieved_password == password)
    {
        return 1; /* Password match */
    }
    else
    {
        return 0; /* Password does not match */
    }
}

void APP_keypadToVariable(uint8* variable)
{
	uint8 key;
	while (1)
	{
		key = KEYPAD_getPressedKey(); /* Call function to get the pressed key */

        /* Check if the key is a number between 0 and 9 */
        if ((key <= 9 && key >= 0))
        {
            /* Update the variable with the new digit */
            *variable = ((*variable * 10) + key);

            /* Display '*' on the LCD for each digit entered */
            LCD_displayCharacter('*');
        }

        /* Handler for use of '=' button, returns to the caller function */
        else if (key == '=' && *variable != 0)
        {
            break;
        }

        /* Handler for 'Enter' key (ASCII 13), resets the variable and clears LCD */
        else if (key == 13 && *variable != 0)
        {
            *variable = 0;

            /* Clear the LCD display */
            LCD_displayStringRowColumn(1, 0, "             ");
            LCD_moveCursor(1, 0);
        }
        /* Delay for de-bouncing */
        _delay_ms(350);
	}
}

void APP_deinit_passwords(void)
{
    /* Reset the password status to indicate no password is set */
    g_passwordIsSet = False;

    /* Clear the new password */
    g_new_password = 0;

    /* Clear the confirmed password */
    g_confirm_password = 0;
}

/*******************************************************************************
 *                              Timer Functions                                *
 *******************************************************************************/

void Timer_countTicks(void)
{
	ticks++;
}

void Timer_delaySeconds(uint16 seconds)
{
	Timer1_init(&timer_config);
	while(ticks != seconds);
	Timer1_deinit();
	ticks = 0;
}
