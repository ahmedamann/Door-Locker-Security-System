 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART Driver
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/

#ifndef MCAL_UART_H_
#define MCAL_UART_H_

/*******************************************************************************
 *                                Types Definitions                            *
 *******************************************************************************/
typedef enum
{
    BAUD_RATE_10 = 10, BAUD_RATE_300 = 300, BAUD_RATE_600 = 600, BAUD_RATE_1200 = 1200,
    BAUD_RATE_2400 = 2400, BAUD_RATE_4800 = 4800, BAUD_RATE_9600 = 9600, BAUD_RATE_14400 = 14400
} UART_BaudRateType;

typedef enum
{
    FIVE_BITS, SIX_BITS, SEVEN_BITS, EIGHT_BITS
} UART_DataType;

typedef enum
{
    DISABLE, EVEN = 2, ODD = 3
} UART_ParityType;

typedef enum
{
    ONE_BIT, TWO_BITS
} UART_StopBitType;

typedef struct
{
    UART_BaudRateType baudrate;
    UART_DataType data;
    UART_ParityType parity;
    UART_StopBitType stop;
} UART_ConfigType;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Initialization function of the UART Driver */
void UART_init(UART_ConfigType* Config_Ptr);

/* Function responsible for sending a byte to another UART device. */
void UART_sendByte(const uint8 data);

/* Function responsible for receiving a byte from another UART device. */
uint8 UART_receiveByte(void);

/* Send the required string through UART to the other UART device. */
void UART_sendString(const uint8* str);

/* Receive the required string until the '#' symbol through UART from the other UART device. */
void UART_receiveString(uint8* str);


#endif /* MCAL_UART_H_ */
