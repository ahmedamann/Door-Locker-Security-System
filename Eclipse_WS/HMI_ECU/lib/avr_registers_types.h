/*
 *  File: avr_registers_types.h
 *
 *  Created on: Jun 15, 2024
 *  Author: Ahmed Aman
 */

#ifndef LIB_AVR_REGISTERS_TYPES_H_
#define LIB_AVR_REGISTERS_TYPES_H_

#include "std_types.h"

typedef union {
    uint8 byte;                 // 8-bit unsigned integer
    struct {
        uint8 pin0: 1;          // Pin 0
        uint8 pin1: 1;          // Pin 1
        uint8 pin2: 1;          // Pin 2
        uint8 pin3: 1;          // Pin 3
        uint8 pin4: 1;          // Pin 4
        uint8 pin5: 1;          // Pin 5
        uint8 pin6: 1;          // Pin 6
        uint8 pin7: 1;          // Pin 7
    } bits;                     // Individual bit access
} GPIO_TYPE;

typedef union {
    uint8 byte;                 // 8-bit unsigned integer
    struct {
        uint8 ISC00: 1;         // Interrupt Sense Control 00
        uint8 ISC01: 1;         // Interrupt Sense Control 01
        uint8 ISC10: 1;         // Interrupt Sense Control 10
        uint8 ISC11: 1;         // Interrupt Sense Control 11
        uint8 SM0: 1;           // Sleep Mode 0
        uint8 SM1: 1;           // Sleep Mode 1
        uint8 SE: 1;            // Sleep Enable
        uint8 SM2: 1;           // Sleep Mode 2
    } bits;                     // Individual bit access
} MCUCR;                        // MCU Control Register

/* MCU Control and Status Register Type */
typedef union {
    uint8 byte;                 // 8-bit unsigned integer
    struct {
        uint8 PORF: 1;          // Power-on Reset Flag
        uint8 EXTRF: 1;         // External Reset Flag
        uint8 BORF: 1;          // Brown-out Reset Flag
        uint8 WDRF: 1;          // Watchdog Reset Flag
        uint8 JTRF: 1;          // JTAG Reset Flag
        uint8 : 3;              // Reserved bits
    } bits;                     // Individual bit access
} MCUCSR;

/* Timer/Counter Control Register Type */
typedef union {
    uint8 byte;                 // 8-bit unsigned integer
    struct {
        uint8 CS00: 1;          // Clock Select 00
        uint8 CS01: 1;          // Clock Select 01
        uint8 CS02: 1;          // Clock Select 02
        uint8 WGM01: 1;         // Waveform Generation Mode 01
        uint8 COM00: 1;         // Compare Match Output Mode 00
        uint8 COM01: 1;         // Compare Match Output Mode 01
        uint8 WGM00: 1;         // Waveform Generation Mode 00
        uint8 FOC0: 1;          // Force Output Compare
    } bits;                     // Individual bit access
} TCCR0;

/* Timer/Counter Register Type */
typedef union {
    uint8 byte;                 // 8-bit unsigned integer
} TCNT0;

/* Oscillator Control and Status Register Type */
typedef union {
    uint8 byte;                 // 8-bit unsigned integer
} OCDR;

/* Special Function IO Register Type */
typedef union {
    uint8 byte;                 // 8-bit unsigned integer
    struct {
        uint8 PSR10: 1;         // Prescaler Reset 10
        uint8 PSR2: 1;          // Prescaler Reset 2
        uint8 PUD: 1;           // Pull-up Disable
        uint8 ACME: 1;          // Analog Comparator Multiplexer Enable
        uint8 : 1;              // Reserved bit
        uint8 ADTS0: 1;         // ADC Trigger Select 0
        uint8 ADTS1: 1;         // ADC Trigger Select 1
        uint8 ADTS2: 1;         // ADC Trigger Select 2
    } bits;                     // Individual bit access
} SFIOR;

/* Timer/Counter 1 Control Register A Type */
typedef union {
    uint8 byte;                 // 8-bit unsigned integer
    struct {
        uint8 WGM10: 1;         // Waveform Generation Mode 10
        uint8 WGM11: 1;         // Waveform Generation Mode 11
        uint8 FOC1B: 1;         // Force Output Compare B
        uint8 FOC1A: 1;         // Force Output Compare A
        uint8 COM1B0: 1;        // Compare Match Output B 0
        uint8 COM1B1: 1;        // Compare Match Output B 1
        uint8 COM1A0: 1;        // Compare Match Output A 0
        uint8 COM1A1: 1;        // Compare Match Output A 1
    } bits;                     // Individual bit access
} TCCR1A;

/* Timer/Counter 1 Control Register B Type */
typedef union {
    uint8 byte;                 // 8-bit unsigned integer
    struct {
        uint8 CS10: 1;          // Clock Select 10
        uint8 CS11: 1;          // Clock Select 11
        uint8 CS12: 1;          // Clock Select 12
        uint8 WGM12: 1;         // Waveform Generation Mode 12
        uint8 WGM13: 1;         // Waveform Generation Mode 13
        uint8 : 2;              // Reserved bits
        uint8 ICNC1: 1;         // Input Capture Noise Canceler 1
    } bits;                     // Individual bit access
} TCCR1B;

/* Output Compare Register Type */
typedef union {
    uint8 byte;                 // 8-bit unsigned integer
} OCR0;

typedef union {
    uint8 byte;                 // 8-bit unsigned integer
    struct {
        uint8 MUX0: 1;          // Multiplexer Input Selection Bit 0
        uint8 MUX1: 1;          // Multiplexer Input Selection Bit 1
        uint8 MUX2: 1;          // Multiplexer Input Selection Bit 2
        uint8 MUX3: 1;          // Multiplexer Input Selection Bit 3
        uint8 MUX4: 1;          // Multiplexer Input Selection Bit 4
        uint8 ADLAR: 1;         // ADC Left Adjust Result
        uint8 REFS0: 1;         // Reference Selection Bit 0
        uint8 REFS1: 1;         // Reference Selection Bit 1
    } bits;                     // Individual bit access
} ADMUX;

typedef union {
    uint8 byte;                 // 8-bit unsigned integer
    struct {
        uint8 ADPS0: 1;         // ADC Prescaler Select Bit 0
        uint8 ADPS1: 1;         // ADC Prescaler Select Bit 1
        uint8 ADPS2: 1;         // ADC Prescaler Select Bit 2
        uint8 ADIE: 1;          // ADC Interrupt Enable
        uint8 ADIF: 1;          // ADC Interrupt Flag
        uint8 ADATE: 1;         // ADC Auto Trigger Enable
        uint8 ADSC: 1;          // ADC Start Conversion
        uint8 ADEN: 1;          // ADC Enable
    } bits;                     // Individual bit access
} ADCSRA;

typedef union {
    uint16 twoBytes;            // 16-bit unsigned integer
    struct {
        uint16 ADC0: 1;         // ADC Channel 0
        uint16 ADC1: 1;         // ADC Channel 1
        uint16 ADC2: 1;         // ADC Channel 2
        uint16 ADC3: 1;         // ADC Channel 3
        uint16 ADC4: 1;         // ADC Channel 4
        uint16 ADC5: 1;         // ADC Channel 5
        uint16 ADC6: 1;         // ADC Channel 6
        uint16 ADC7: 1;         // ADC Channel 7
        uint16 ADC8: 1;         // ADC Channel 8
        uint16 ADC9: 1;         // ADC Channel 9
        uint16 ADC10: 1;        // ADC Channel 10
        uint16 ADC11: 1;        // ADC Channel 11
        uint16 ADC12: 1;        // ADC Channel 12
        uint16 ADC13: 1;        // ADC Channel 13
        uint16 ADC14: 1;        // ADC Channel 14
        uint16 ADC15: 1;        // ADC Channel 15
    } bits;                     // Individual bit access
} ADC;

#define PORTA   (*(volatile GPIO_TYPE *)0x3B)  // Port A Data Register
#define DDRA    (*(volatile GPIO_TYPE *)0x3A)  // Port A Data Direction Register
#define PINA    (*(volatile GPIO_TYPE *)0x39)  // Port A Input Pins Register

#define PORTB   (*(volatile GPIO_TYPE *)0x38)  // Port B Data Register
#define DDRB    (*(volatile GPIO_TYPE *)0x37)  // Port B Data Direction Register
#define PINB    (*(volatile GPIO_TYPE *)0x36)  // Port B Input Pins Register

#define PORTC   (*(volatile GPIO_TYPE *)0x35)  // Port C Data Register
#define DDRC    (*(volatile GPIO_TYPE *)0x34)  // Port C Data Direction Register
#define PINC    (*(volatile GPIO_TYPE *)0x33)  // Port C Input Pins Register

#define PORTD   (*(volatile GPIO_TYPE *)0x32)  // Port D Data Register
#define DDRD    (*(volatile GPIO_TYPE *)0x31)  // Port D Data Direction Register
#define PIND    (*(volatile GPIO_TYPE *)0x30)  // Port D Input Pins Register

#define SREG    (*(volatile SREG*)0x5F)     // Status Register
#define OCR0    (*(volatile OCR0*)0x5C)     // Output Compare Register 0
#define GICR    (*(volatile GICR*)0x5B)     // General Interrupt Control Register
#define GIFR    (*(volatile GIFR*)0x5A)     // General Interrupt Flag Register
#define TIMSK   (*(volatile TIMSK*)0x59)    // Timer/Counter Interrupt Mask Register
#define TIFR    (*(volatile TIFR*)0x58)     // Timer/Counter Interrupt Flag Register
#define SPMCR   (*(volatile SPMCR*)0x57)    // Store Program Memory Control Register
#define TWCR    (*(volatile TWCR*)0x56)     // Two-wire Serial Interface Control Register
#define MCUCR   (*(volatile MCUCR*)0x55)    // MCU Control Register
#define MCUCSR  (*(volatile MCUCSR*)0x54)   // MCU Control and Status Register
#define TCCR0   (*(volatile TCCR0*)0x53)    // Timer/Counter Control Register 0
#define TCNT0   (*(volatile TCNT0*)0x52)    // Timer/Counter Register 0
#define SFIOR   (*(volatile SFIOR*)0x50)    // Special Function IO Register
#define TCCR1A  (*(volatile TCCR1A*)0x4F)   // Timer/Counter 1 Control Register A
#define TCCR1B  (*(volatile TCCR1B*)0x4E)   // Timer/Counter 1 Control Register B
#define TCNT1   (*(volatile TCNT1*)0x4C)    // Timer/Counter 1 Register
#define OCR1A   (*(volatile OCR1A*)0x4A)    // Output Compare Register 1 A
#define OCR1B   (*(volatile OCR1B*)0x48)    // Output Compare Register 1 B
#define ICR1    (*(volatile ICR1*)0x46)     // Input Capture Register 1
#define TCCR2   (*(volatile TCCR2*)0x45)    // Timer/Counter Control Register 2
#define TCNT2   (*(volatile TCNT2*)0x44)    // Timer/Counter Register 2
#define OCR2    (*(volatile OCR2*)0x43)     // Output Compare Register 2
#define WDTCR   (*(volatile WDTCR*)0x41)    // Watchdog Timer Control Register
#define UBRRH   (*(volatile UBRRH*)0x40)    // USART Baud Rate Register High
#define UCSRC   (*(volatile UCSRC*)0x40)    // USART Control and Status Register C
#define SPDR    (*(volatile SPDR*)0x2F)     // SPI Data Register
#define SPSR    (*(volatile SPSR*)0x2E)     // SPI Status Register
#define SPCR    (*(volatile SPCR*)0x2D)     // SPI Control Register
#define UDR     (*(volatile UDR*)0x2C)      // USART I/O Data Register
#define UCSRA   (*(volatile UCSRA*)0x2B)    // USART Control and Status Register A
#define UCSRB   (*(volatile UCSRB*)0x2A)    // USART Control and Status Register B
#define UBRRL   (*(volatile UBRRL*)0x29)    // USART Baud Rate Register Low
#define ACSR    (*(volatile ACSR*)0x28)     // Analog Comparator Control and Status Register
#define ADMUX   (*(volatile ADMUX*)0x27)    // ADC Multiplexer Selection Register
#define ADCSRA  (*(volatile ADCSRA*)0x26)   // ADC Control and Status Register A
#define ADC     (*(volatile ADC*)0x24)      // ADC Data Register

#endif /* LIB_AVR_REGISTERS_TYPES_H_ */
