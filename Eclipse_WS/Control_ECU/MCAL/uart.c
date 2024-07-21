 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART Driver
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/

/*******************************************************************************
 *                              Included Files                                 *
 *******************************************************************************/

#include <avr/io.h>
#include "../lib/std_types.h"
#include "../lib/common_macros.h"
#include "uart.h"

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/


/* Function name: UART_init,
 * This is the initialization function to configure the settings for the UART
 */

/* Initialization function of the UART Driver */
void UART_init(UART_ConfigType* Config_Ptr)
{
    /* Value to be written in UBRR Register according to baud rate */
    uint16 ubrr_value = 0;

    UCSRA = (1 << U2X); /* Asynchronous with double the UART transmission speed */
    UCSRB = (1 << TXEN) | (1 << RXEN); /* Tx enable and Rx enable */

    /* Set URSEL to 1 to access UCSRC */
    UCSRC = (1 << URSEL);
    /* Choose the Parity */
    UCSRC = (UCSRC & 0xCF) | (Config_Ptr->parity << 4);

    /* Choose the Stop Bits */
    UCSRC = (UCSRC & ~(1 << USBS)) | (Config_Ptr->stop << USBS);

    /* Choose the data length */
    switch (Config_Ptr->data)
    {
        case FIVE_BITS:
            UCSRB &= ~(1 << UCSZ2);
            UCSRC &= ~((1 << UCSZ1) | (1 << UCSZ0));
            break;
        case SIX_BITS:
            UCSRB &= ~(1 << UCSZ2);
            UCSRC = (UCSRC & ~(1 << UCSZ1)) | (1 << UCSZ0);
            break;
        case SEVEN_BITS:
            UCSRB &= ~(1 << UCSZ2);
            UCSRC = (UCSRC & ~(1 << UCSZ0)) | (1 << UCSZ1);
            break;
        case EIGHT_BITS:
            UCSRB &= ~(1 << UCSZ2);
            UCSRC |= (1 << UCSZ1) | (1 << UCSZ0);
            break;
    }

    /* Calculate the value to be written in UBRR Register according to baud rate */
    ubrr_value = (uint16)(((F_CPU / (8UL * Config_Ptr->baudrate))) - 1);

    /* Write the UBRR value */
    UBRRH = (uint8)(ubrr_value >> 8);
    UBRRL = (uint8)ubrr_value;
}

/* Function responsible for sending a byte to another UART device. */
void UART_sendByte(const uint8 data)
{
    /* Wait for the UDRE Flag to be set indicating that the UDR register is empty */
    while (!(UCSRA & (1 << UDRE)));

    /* Put the required data to be sent in the UDR Register */
    UDR = data;
}

/* Function responsible for receiving a byte from another UART device. */
uint8 UART_receiveByte(void)
{
    /* Wait for the RXC Flag to be set indicating that the UART finished receiving the data */
    while (!(UCSRA & (1 << RXC)));

    /* Read the data received from the UDR Register */
    return UDR;
}

/* Send the required string through UART to the other UART device. */
void UART_sendString(const uint8* str)
{
    /* Send the whole string byte by byte */
    while (*str != '\0')
    {
        UART_sendByte(*str);
        str++;
    }
}

/* Receive the required string until the '#' symbol through UART from the other UART device. */
void UART_receiveString(uint8* str)
{
    /* Counter */
    uint8 i = 0;

    /* Receive first byte */
    str[i] = UART_receiveByte();

    while (str[i] != '#') /* # is the key for sending and receiving */
    {
        /* Receive new byte from the string in the next free location */
        i++;
        str[i] = UART_receiveByte();
    }

    str[i] = '\0'; /* Put the null terminator for the string */
}

