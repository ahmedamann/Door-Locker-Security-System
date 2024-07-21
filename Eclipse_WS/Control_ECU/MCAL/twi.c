 /******************************************************************************
 *
 * Module: twi
 *
 * File Name: twi.c
 *
 * Description: The Source File for the twi Driver.
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
#include "twi.h"

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

void TWI_init(TWI_ConfigType* config)
{
    /* Set the bit rate for TWI communication */
    TWI_BIT_RATE(config->bitRate);

    /* Set the slave address */
    TWAR = config->address;

    /* Enable the TWI module */
    TWCR = (1 << TWEN);
}

void TWI_start(void)
{
    /* Send the start condition */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    /* Wait for the start condition to be transmitted */
    while(BIT_IS_CLEAR(TWCR, TWINT));
}

void TWI_stop(void)
{
    /* Send the stop condition */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_writeByte(uint8 data)
{
    /* Load data into TWI data register */
    TWDR = data;

    /* Start data transmission */
    TWCR = (1 << TWINT) | (1 << TWEN);

    /* Wait for the data transmission to complete */
    while(BIT_IS_CLEAR(TWCR, TWINT));
}

uint8 TWI_readByteWithACK(void)
{
    /* Enable ACK and start data reception */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    /* Wait for the data reception to complete */
    while(BIT_IS_CLEAR(TWCR, TWINT));

    /* Return the received data */
    return TWDR;
}

uint8 TWI_readByteWithNACK(void)
{
    /* Start data reception without sending ACK */
    TWCR = (1 << TWINT) | (1 << TWEN);

    /* Wait for the data reception to complete */
    while(BIT_IS_CLEAR(TWCR, TWINT));

    /* Return the received data */
    return TWDR;
}

uint8 TWI_getStatus(void)
{
    /* Return the status register value */
    return TWI_STATUS_REG;
}

