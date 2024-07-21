 /******************************************************************************
 *
 * Module: app
 *
 * File Name: app.c
 *
 * Description: The Source File for the application.
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../HAL/eeprom.h"
#include "../HAL/dc_motor.h"
#include "../HAL/buzzer.h"
#include "../MCAL/twi.h"
#include "../MCAL/uart.h"
#include "helper.h"

uint8 volatile ticks = 0;

/* Timer configuration structure */
Timer_ConfigType timer_config = {
    .initial_value = 0,
    .compare_value = COMPARE_VALUE,
    .prescaler = F_CPU_1024,
    .mode = COMPARE_MODE
};

int main (void)
{
    /* Enable global interrupts */
    sei();

    /* Set the timer callback function */
    Timer1_setCallBack(Timer_countTicks);

    /* Initialize the DC motor and buzzer */
    DCMotor_Init();
    Buzzer_init();

    /* UART Configurations
     * Baud Rate: 9600 bps
     * Data size: Eight bit data
     * Error Checking: Even Parity
     * Stop bits: one
     */
    UART_ConfigType uart_config = {BAUD_RATE_9600, EIGHT_BITS, EVEN, ONE_BIT};
    UART_init(&uart_config);

    /* TWI (I2C) Configurations
     * Bit rate: 400kbps
     * EEPROM address
     */
    TWI_ConfigType twi_config = {LOC_2, TWI_400KB};
    TWI_init(&twi_config);

    while(1)
    {
        /* Handle received UART commands */
        switch (UART_receiveByte()) {
            case CODE_RETREIVE_PASSWORD:
                APP_sendPassword();
                break;

            case CODE_SAVE_PASSWORD:
                APP_savePassword();
                break;

            case CODE_OPEN_DOOR:
                APP_openDoorHandler();
                break;

            case CODE_ACTIVATE_BUZZER:
                APP_activateBuzzer();
                break;

            default:
                break;
        }
    }
}

/* Function to handle door opening process */
void APP_openDoorHandler(void)
{
    DCMotor_Rotate(CW);       /* Motor opening the door */
    Timer_delaySeconds(15);    /* Time for opening the door */

    DCMotor_Rotate(STOP);     /* The door opened, so stopping motor */
    Timer_delaySeconds(3);    /* The time for keeping the door open */

    DCMotor_Rotate(ACW);      /* Motor closing the door */
    Timer_delaySeconds(15);    /* Time for closing the door */

    DCMotor_Rotate(STOP);     /* The door closed, so stopping motor */
}

/* Function to save password to EEPROM */
void APP_savePassword(void)
{
    uint8 password;
    password = UART_receiveByte();
    EEPROM_writeByte(EEPROM_PASSWORD_LOCATION, password);
}

/* Function to send password from EEPROM via UART */
void APP_sendPassword(void)
{
    uint8 password;
    EEPROM_readByte(EEPROM_PASSWORD_LOCATION, &password);
    UART_sendByte(password);
}

/* Function to activate the buzzer */
void APP_activateBuzzer(void)
{
    Buzzer_on();
    Timer_delaySeconds(60);    /* Keep buzzer on for 1 second */
    Buzzer_off();
}

/*******************************************************************************
 *                              Timer Functions                                *
 *******************************************************************************/

/* Timer tick callback function */
void Timer_countTicks(void)
{
    ticks++;
}

/* Function to create a delay in seconds using the timer */
void Timer_delaySeconds(uint16 seconds)
{
    Timer1_init(&timer_config);
    while(ticks != seconds);
    Timer1_deinit();
    ticks = 0;
}
