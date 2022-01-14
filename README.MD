# Programmable laboratory bench power supply

Programmable laboratory bench PSU, consisting of linear regulator and switching
preregulator.

![lab bench psu](https://github.com/BojanSof/Lab-Bench-PSU/blob/main/images/psu.jpg)

## Block diagram

![block diagram](https://github.com/BojanSof/Lab-Bench-PSU/blob/main/images/block.png)

I used transformer just because I had it laying around.

The switching preregulator is actually buck converter realised with LM2576-ADJ
and it keeps constant 1.5 V on the LDO.

The MCU I used is PIC16F18855, which is very easily available in my country and
it is pretty cheap. It has 10-bit ADC and maximum PWM resolution of 10 bits.

The MCU samples the output, divided by 3 with voltage divider, to obtain the
output voltage value, and the output from the differential amplifier whose 
output is proportional to the voltage of the shunt resistor.

The LDO is realised with TIP41 pass transistor and LM324 operational amplifier
among the main components.

The LCD is 2 rows by 16 columns, with HD44780 controller and the interface to 
the MCU is done via I2C I/O expander (PCF8574).

## Goal specifications

Voltage: 0 - 15 V, with steps of 15 mV
Current: 0 - 1 A, with steps of 5 mA

Additional software modifications and testing is required to meet these 
specifications, especially the current limit one.

## PCB and schematic

The schematic and PCB design is created in KiCad.

The PCB is single layer because I made it in my home. I only used THT
components for the whole design.

## Firmware

The firmware is developed using MPLAB X IDE, with the free version of the XC8 
compiler.
