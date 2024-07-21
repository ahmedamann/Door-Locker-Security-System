 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: Source file for the GPIO Driver.
 *
 * Author: Ahmed Aman
 *
 ********************************************************************************/
#include "../LIB/std_types.h" /* For the standard types */
#include "../LIB/avr_registers_types.h" /* For registers types */
#include "../LIB/common_macros.h" /* For common macros */

#include "gpio.h"

volatile GPIO_TYPE* DIRECTION_REG[4] = {&DDRA, &DDRB, &DDRC, &DDRD};
volatile GPIO_TYPE* WRITE_REG[4] = {&PORTA, &PORTB, &PORTC, &PORTD};
volatile GPIO_TYPE* READ_REG[4] = {&PINA, &PINB, &PINC, &PIND};

/*
 * Description:
 * Sets the direction (input or output) of a specific pin in a given port.
 * If the port number, pin number, or direction are invalid, the function does nothing.
 *
 * Parameters:
 * - port_num: Port number where the pin is located.
 * - pin_num: Pin number within the port (0 to NUM_OF_PINS_PER_PORT-1).
 * - direction: Desired direction of the pin (PIN_OUTPUT or PIN_INPUT).
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction) {
    if (pin_num < NUM_OF_PINS_PER_PORT) {
        if (direction == PIN_OUTPUT) {
            DIRECTION_REG[port_num]->byte |= (1 << pin_num); // Set pin as output
        } else if (direction == PIN_INPUT) {
            DIRECTION_REG[port_num]->byte &= ~(1 << pin_num); // Set pin as input
        }
    }
}

/*
 * Description:
 * Sets the direction (input or output) of a range of consecutive pins in a given port.
 * If the port number, pin range, or direction are invalid, the function does nothing.
 *
 * Parameters:
 * - first_pin_num: First pin number in the range (0 to NUM_OF_PINS_PER_PORT-1).
 * - last_pin_num: Last pin number in the range (0 to NUM_OF_PINS_PER_PORT-1).
 * - port_num: Port number where the pins are located.
 * - direction: Desired direction of the pins (PIN_OUTPUT or PIN_INPUT).
 */
void GPIO_setupPinDirectionR(uint8 first_pin_num, uint8 last_pin_num, uint8 port_num, GPIO_PinDirectionType direction)
{
    if ((first_pin_num < NUM_OF_PINS_PER_PORT) && (last_pin_num < NUM_OF_PINS_PER_PORT) && (port_num < NUM_OF_PORTS)) {
        if (last_pin_num > first_pin_num) {
            for (uint8 i = 0; i <= (last_pin_num - first_pin_num); i++) {
                GPIO_setupPinDirection(port_num, first_pin_num + i, direction);
            }
        }
    }
}

/*
 * Description:
 * Writes a logic high or logic low value to a specified pin.
 * If the port number or pin number are invalid, the function does nothing.
 * If the pin is configured as input, this function enables/disables the internal pull-up resistor.
 *
 * Parameters:
 * - port_num: Port number where the pin is located.
 * - pin_num: Pin number within the port (0 to NUM_OF_PINS_PER_PORT-1).
 * - value: Logic level to be written (LOGIC_HIGH or LOGIC_LOW).
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
    if (pin_num < NUM_OF_PINS_PER_PORT && port_num < NUM_OF_PORTS) {
        if (value == LOGIC_HIGH) {
            WRITE_REG[port_num]->byte |= (1 << pin_num); // Set pin to logic high
        } else if (value == LOGIC_LOW) {
            WRITE_REG[port_num]->byte &= ~(1 << pin_num); // Set pin to logic low
        }
    }
}

/*
 * Description:
 * Reads and returns the logic level (logic high or logic low) of a specified pin.
 * If the port number or pin number are invalid, the function returns logic low.
 *
 * Parameters:
 * - port_num: Port number where the pin is located.
 * - pin_num: Pin number within the port (0 to NUM_OF_PINS_PER_PORT-1).
 * Returns:
 * - Logic level of the pin (LOGIC_HIGH or LOGIC_LOW).
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
    uint8 pin_value = LOGIC_LOW;

    if (pin_num < NUM_OF_PINS_PER_PORT && port_num < NUM_OF_PORTS) {
        if (READ_REG[port_num]->byte & (1 << pin_num)) {
            pin_value = LOGIC_HIGH; // Pin is logic high
        }
    }

    return pin_value;
}

/*
 * Description:
 * Sets the direction (input or output) of all pins in a specified port.
 * If the port number is invalid, the function does nothing.
 *
 * Parameters:
 * - port_num: Port number where all pins are located.
 * - direction: Desired direction of the port (PORT_INPUT or PORT_OUTPUT).
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
    if (port_num < NUM_OF_PORTS) {
        DIRECTION_REG[port_num]->byte = direction; // Set port direction
    }
}

/*
 * Description:
 * Writes a value to all pins in a specified port.
 * If any pin in the port is configured as output, the value is written to all pins.
 * If any pin in the port is configured as input, this function enables/disables internal pull-up resistors.
 * If the port number is invalid, the function does nothing.
 *
 * Parameters:
 * - port_num: Port number where all pins are located.
 * - value: Value to be written to the port.
 */
void GPIO_writePort(uint8 port_num, uint8 value)
{
    if (port_num < NUM_OF_PORTS) {
        WRITE_REG[port_num]->byte = value; // Write value to port
    }
}

/*
 * Description:
 * Reads and returns the value of all pins in a specified port.
 * If the port number is invalid, the function returns zero.
 *
 * Parameters:
 * - port_num: Port number to read from.
 * Returns:
 * - Value read from the port.
 */
uint8 GPIO_readPort(uint8 port_num)
{
    uint8 value = LOGIC_LOW;

    if (port_num < NUM_OF_PORTS) {
        value = READ_REG[port_num]->byte; // Read value from port
    }

    return value;
}

