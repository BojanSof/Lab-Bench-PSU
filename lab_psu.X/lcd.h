/* 
 * File:   lcd.h
 * Author: bojan
 * Library for driving 16x2 LCD with I2C IO expander
 * The LCD controller/driver is HD44780
 * The I2C IO expander is PCF8574
 * PCF8574 and HD44780 Connection:
 * P7   <->     DB7
 * P6   <->     DB6
 * P5   <->     DB5
 * P4   <->     DB4
 * P3   <->     BACKLIGHT
 * P2   <->     EN
 * P1   <->     R_nW
 * P0   <->     RS
 * Created on September 16, 2021, 2:54 PM
 */

#ifndef LCD_H
#define	LCD_H

#include <pic.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define LCD_RS              0x01U
#define LCD_RW              0x02U
#define LCD_EN              0x04U
#define LCD_BACKLIGHT       0x08U
// LCD commands
#define LCD_CLEAR_CMD       0x01U
#define LCD_HOME_CMD        0x02U
#define LCD_ON_CMD          0x0CU
#define LCD_OFF_CMD         0x08U
#define LCD_CURSOR_ON_CMD   0x0EU
#define LCD_BLINKING_ON_CMD 0x0DU
#define LCD_SET_DDRAM_ADDR_CMD  0x80U
#define LCD_SET_CGRAM_ADDR_CMD  0x40U

typedef struct LCD {
    uint8_t address;
    
    char data[32];
    uint8_t pos;
    uint8_t backlight;
} LCD;    

/**
 * \brief Write data to the I2C IO Expander
 *
 * \param[in] lcd Pointer to LCD structure
 * \param[in] data The data to write
 *
 * \return Nothing
 */
void IO_Expander_write(LCD *lcd, uint8_t data);

/**
 * \brief Write nibble to the LCD controller/Driver
 *
 * \param[in] lcd Pointer to LCD structure
 * \param[in] data The data to write
 * \param[in] isCommand 1 if the data to be send are command, 0 if they are character data
 *
 * \return Nothing
 */
void LCD_writeNibble(LCD *lcd, uint8_t nibble, uint8_t isCommand);

/**
 * \brief Write byte to the LCD controller/driver
 *
 * \param[in] lcd Pointer to LCD structure
 * \param[in] data The data to write
 * \param[in] isCommand 1 if the data to be send are command, 0 if they are character data
 *
 * \return Nothing
 */
void LCD_write(LCD *lcd, uint8_t data, uint8_t isCommand);

/**
 * \brief Initialize the LCD controller/driver
 *
 * \param[in] lcd Pointer to LCD structure
 *
 * \return Nothing
 */
void LCD_init(LCD *lcd, uint8_t address);

/**
 * \brief Clear the content of the LCD
 *
 * \param[in] lcd Pointer to LCD structure
 * \param[in] address Address of the i2c IO expander
 *
 * \return Nothing
 */
void LCD_clear(LCD *lcd);

/**
 * \brief Move the pointer to the upper-left of the LCD
 *
 * \param[in] lcd Pointer to LCD structure
 *
 * \return Nothing
 */
void LCD_home(LCD *lcd);

/**
 * \brief Turn the display ON
 *
 * \param[in] lcd Pointer to LCD structure
 *
 * \return Nothing
 */
void LCD_on(LCD *lcd);

/**
 * \brief Turn the display OFF
 *
 * \param[in] lcd Pointer to LCD structure
 *
 * \return Nothing
 */
void LCD_off(LCD *lcd);

/**
 * \brief Turn the backlight ON
 *
 * \param[in] lcd Pointer to LCD structure
 *
 * \return Nothing
 */
void LCD_backlightON(LCD *lcd);

/**
 * \brief Turn the backlight OFF
 *
 * \param[in] lcd Pointer to LCD structure
 *
 * \return Nothing
 */
void LCD_backlightOFF(LCD *lcd);

/**
 * \brief Set the cursor to the specified row and column
 *
 * \param[in] lcd Pointer to LCD structure
 * \param[in] row The row to set the cursor
 * \param[in] col The column to set the cursor
 *
 * \return Nothing
 */
void LCD_setCursor(LCD *lcd, uint8_t row, uint8_t col);

/**
 * \brief Print a single character to the LCD
 *
 * \param[in] lcd Pointer to LCD structure
 * \param[in] c The character to print
 *
 * \return Nothing
 */
void LCD_printCustomChar(LCD *lcd, uint8_t n);

/**
 * \brief Print a custom char from the CGRAM
 *
 * \param[in] lcd Pointer to LCD structure
 * \param[in] n The number of the custom character (0 to 7)
 *
 * \return Nothing
 */
void LCD_printChar(LCD *lcd, char c);

/**
 * \brief Print a null-terminated string to the LCD
 *
 * \param[in] lcd Pointer to LCD structure
 * \param[in] str The string to print
 *
 * \return Nothing
 */
void LCD_print(LCD *lcd, char *str);

/**
 * \brief Write a custom char in the CGRAM
 *
 * \param[in] lcd Pointer to LCD structure
 * \param[in] n The number of the custom character (0 to 7)
 * \param[in] c Array with 8 5-bit numbers which represent the state of the dot of the segment (on/off)
 *
 * \return Nothing
 */
void LCD_createCustomChar(LCD *lcd, uint8_t n, uint8_t c[8]);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

