Smart Automatic Water Tank Management System
A smart embedded system developed using the LPC2129 ARM7 Microcontroller to automatically monitor and control water levels in storage tanks. The system reads water level data through ADC, displays real-time information on a 16x2 LCD, and automatically switches the water pump ON or OFF based on the tank level.

Features
Automatic water level monitoring
Automatic pump control
16x2 LCD display (4-bit mode)
ADC-based water level sensing
Timer-based delay implementation
Water overflow prevention
Reduced manual intervention
Low-cost and reliable solution
Hardware Used
LPC2129 ARM7 Microcontroller
Water Level Sensor
16x2 LCD Display
Relay Module
Water Pump
Power Supply
Working
The water level sensor continuously measures the tank level and sends the data to the LPC2129 through the ADC. The controller converts the ADC value into a percentage and displays it on the LCD. When the water level falls below a predefined threshold, the pump is automatically turned ON. Once the tank reaches the required level, the pump is switched OFF, preventing water overflow and saving electricity.

Technologies
Embedded C
ARM7 LPC2129
ADC Interfacing
LCD Interfacing
Timer Programming
Embedded System Design
