# Door Locker Security System

This project is a door locker security system consisting of two main Electronic Control Units (ECUs):

- **Human-Machine Interface (HMI) ECU**: Interfaces with the user.
- **Control ECU**: Manages system operations and control.

## Microcontroller

- **ATmega32**

## Implemented Drivers

- **Keypad**: Allows user input for password authentication.
- **LCD**: Displays messages and feedback to the user.
- **DC Motor**: Controls the locking and unlocking mechanism of the door.
- **UART**: Enables communication between the HMI ECU and the Control ECU.
- **Timer**: Manages time-dependent operations within the system.
- **External EEPROM**: Stores essential data, such as user passwords and system settings.

## System Functionality

- **Keypad**: The user is prompted to enter a password to unlock the door. If the password is entered incorrectly multiple times (e.g., three attempts), the system will lock out further attempts for a set period.
- **LCD**: Provides real-time feedback and instructions to the user, such as prompting for the password, displaying access granted or denied messages, and showing lockout status.
- **DC Motor**: Activates to lock or unlock the door based on the authentication result from the Control ECU.
- **UART**: Ensures seamless communication between the HMI ECU and the Control ECU to process user input and control signals.
- **Timer**: Utilized to handle delays, manage lockout periods after incorrect password attempts, and other time-based functions.
- **External EEPROM**: Stores user passwords and other critical data securely, ensuring the system retains necessary information even after power cycles.

## Overview

This door locker security system enhances security by requiring user authentication via a keypad. The user is prompted to enter a password, and the system checks the entered password against stored data in the EEPROM. If authenticated, the DC motor unlocks the door. If the wrong password is entered multiple times, the system temporarily locks out the user to prevent unauthorized access.
