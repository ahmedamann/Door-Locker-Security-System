 /******************************************************************************
 *
 * Module: twi
 *
 * File Name: twi.h
 *
 * Description: The Header File for the twi Driver.
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/

#ifndef MCAL_TWI_H_
#define MCAL_TWI_H_

#define FREQUENCY_CPU 8

/*******************************************************************************
 *                              Included Files                                 *
 *******************************************************************************/

#include <avr/io.h> /* For Using AVR Register Names and Bit Names.*/

#include "../lib/std_types.h" /* For Using Standard Types like "uint8". */

/*******************************************************************************
 *                         Macros for Status Register                          *
 *******************************************************************************/

#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                   Macros for TWI Registers Configurations                   *
 *******************************************************************************/

#define TWI_BIT_RATE(PRESCALER) { \
    TWSR = (TWSR & ~((1 << TWPS1) | (1 << TWPS0))) | (PRESCALER & 0x03); \
    TWBR = 0x02; \
}

#define TWI_POLLING { \
		while(!( TWCR & (1 << TWINT))); \
		TWCR |= (1 << TWINT); \
}

#define TWI_ENABLE_ACK_BIT 					   ( TWCR |= (1 << TWEA) )

#define TWI_START_CONDITION                    ( TWCR |= (1 << TWSTA))

#define TWI_STOP_CONDITION                     ( TWCR |= (1 << TWSTO))

#define TWI_ENABLE_ACK                         ( TWCR = (1 << TWEN) | (1 << TWEA))

#define TWI_ENABLE                             ( TWCR = (1 << TWEN)  )

#define TWI_INTERRUPT_ENABLE                   ( TWCR |= (1 << TWIE) )

#define TWI_STATUS_REG                         ( TWSR & 0xF8        )

#define TWI_DATA_REG                           ( TWDR                )

#define TWI_SLAVE_ADDRESS_REG                  ( TWAR                )

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* For different Bit Rates depending on CPU Frequency */

#if (FREQUENCY_CPU == 8)

typedef enum {
	TWI_200KB, TWI_400KB, TWI_800KB, TWI_1600KB
}TWI_BaudRate;

typedef enum {
	LOC_1 = 0x01, LOC_2 = 0x02, LOC_3 = 0x03, LOC_4 = 0x04
}TWI_Address;

#elif (FREQUENCY_CPU == 16)

typedef enum {
	TWI_400KB, TWI_800KB, TWI_1600KB, TWI_3200KB
}twiBitRateType;

#endif

typedef struct{
	TWI_Address address;
	TWI_BaudRate bitRate;
}TWI_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void TWI_init(TWI_ConfigType* config);

void TWI_start(void);

void TWI_stop(void);

void TWI_writeByte(uint8 data);

uint8 TWI_readByteWithACK(void);

uint8 TWI_readByteWithNACK(void);

uint8 TWI_getStatus(void);

#endif /* MCAL_TWI_H_ */
