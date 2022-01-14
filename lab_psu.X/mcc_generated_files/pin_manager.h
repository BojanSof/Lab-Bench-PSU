/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F18855
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RB0 procedures
#define RB0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define RB0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define RB0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define RB0_GetValue()              PORTBbits.RB0
#define RB0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define RB0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define RB0_SetPullup()             do { WPUBbits.WPUB0 = 1; } while(0)
#define RB0_ResetPullup()           do { WPUBbits.WPUB0 = 0; } while(0)
#define RB0_SetAnalogMode()         do { ANSELBbits.ANSB0 = 1; } while(0)
#define RB0_SetDigitalMode()        do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set Vout aliases
#define Vout_TRIS                 TRISBbits.TRISB2
#define Vout_LAT                  LATBbits.LATB2
#define Vout_PORT                 PORTBbits.RB2
#define Vout_WPU                  WPUBbits.WPUB2
#define Vout_OD                   ODCONBbits.ODCB2
#define Vout_ANS                  ANSELBbits.ANSB2
#define Vout_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define Vout_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define Vout_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define Vout_GetValue()           PORTBbits.RB2
#define Vout_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define Vout_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define Vout_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define Vout_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define Vout_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define Vout_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define Vout_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define Vout_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set Iout aliases
#define Iout_TRIS                 TRISBbits.TRISB3
#define Iout_LAT                  LATBbits.LATB3
#define Iout_PORT                 PORTBbits.RB3
#define Iout_WPU                  WPUBbits.WPUB3
#define Iout_OD                   ODCONBbits.ODCB3
#define Iout_ANS                  ANSELBbits.ANSB3
#define Iout_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define Iout_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define Iout_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define Iout_GetValue()           PORTBbits.RB3
#define Iout_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define Iout_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define Iout_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define Iout_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define Iout_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define Iout_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define Iout_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define Iout_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set RotEncCLK aliases
#define RotEncCLK_TRIS                 TRISCbits.TRISC0
#define RotEncCLK_LAT                  LATCbits.LATC0
#define RotEncCLK_PORT                 PORTCbits.RC0
#define RotEncCLK_WPU                  WPUCbits.WPUC0
#define RotEncCLK_OD                   ODCONCbits.ODCC0
#define RotEncCLK_ANS                  ANSELCbits.ANSC0
#define RotEncCLK_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define RotEncCLK_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define RotEncCLK_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define RotEncCLK_GetValue()           PORTCbits.RC0
#define RotEncCLK_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define RotEncCLK_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define RotEncCLK_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define RotEncCLK_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define RotEncCLK_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define RotEncCLK_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define RotEncCLK_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define RotEncCLK_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set RotEncDT aliases
#define RotEncDT_TRIS                 TRISCbits.TRISC1
#define RotEncDT_LAT                  LATCbits.LATC1
#define RotEncDT_PORT                 PORTCbits.RC1
#define RotEncDT_WPU                  WPUCbits.WPUC1
#define RotEncDT_OD                   ODCONCbits.ODCC1
#define RotEncDT_ANS                  ANSELCbits.ANSC1
#define RotEncDT_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define RotEncDT_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define RotEncDT_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define RotEncDT_GetValue()           PORTCbits.RC1
#define RotEncDT_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define RotEncDT_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define RotEncDT_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define RotEncDT_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define RotEncDT_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define RotEncDT_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define RotEncDT_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define RotEncDT_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set RotEncSW aliases
#define RotEncSW_TRIS                 TRISCbits.TRISC2
#define RotEncSW_LAT                  LATCbits.LATC2
#define RotEncSW_PORT                 PORTCbits.RC2
#define RotEncSW_WPU                  WPUCbits.WPUC2
#define RotEncSW_OD                   ODCONCbits.ODCC2
#define RotEncSW_ANS                  ANSELCbits.ANSC2
#define RotEncSW_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define RotEncSW_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define RotEncSW_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RotEncSW_GetValue()           PORTCbits.RC2
#define RotEncSW_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define RotEncSW_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define RotEncSW_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define RotEncSW_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define RotEncSW_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define RotEncSW_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define RotEncSW_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define RotEncSW_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSC4 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/