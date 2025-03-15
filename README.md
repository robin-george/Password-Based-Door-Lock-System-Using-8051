# Password-Based-Door-Lock-System-Using-8051
This project implements a password-protected door lock system using an 8051 microcontroller, a 4x4 keypad, an LCD display, and a DC motor to indicate door movement. If the correct password is entered, the door opens; otherwise, a buzzer alerts unauthorized access.

# Features:
- **User Authentication:** The system prompts the user to enter a password.  
- **LCD Display:** Shows password entry and system messages.  
- **Keypad Input:** Users enter a predefined password using a **4x4 matrix keypad**.  
- **Motor Control:** A **DC motor** simulates the door opening when the password is correct.  
- **Security Alert:** A **buzzer sounds** when the wrong password is entered.  
- **Predefined Password:** The password is stored in the **8051 microcontroller code**.

# Hardware Components:  
- **8051 Microcontroller** (e.g., AT89S52)  
- **16x2 LCD Display**  
- **4x4 Keypad**  
- **DC Motor** (to simulate door movement)  
- **Buzzer** (for incorrect password alerts)  
- **Power Supply (5V & 12V)**

# Software Used:  
- **Keil µVision** (for Embedded C programming)  
- **Proteus** (for simulation)

# How It Works  
1. The system continuously asks the user to enter a password.  
2. The entered password is compared with the predefined password stored in the microcontroller.  
3. If the password is correct, the **DC motor rotates**, simulating door unlocking.  
4. If the password is incorrect, the **buzzer sounds** as a warning.  
5. The system resets and asks for the password again.

# Code & Circuit Diagram  
Find the complete source code and simulation files in this repository. 

# License  
This project is licensed under the **MIT License**.
