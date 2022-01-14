#include "lcd.h"
#include "mcc_generated_files/mcc.h"

void IO_Expander_write(LCD *lcd, uint8_t data) {
    data |= lcd->backlight;
    //I2C1_WriteNBytes(lcd->address, &data, 1);
    while(!I2C1_Open(lcd->address));
    I2C1_SetBuffer(&data, 1);
    //I2C1_SetAddressNackCallback(NULL,NULL);
    I2C1_MasterWrite();
    while(I2C1_BUSY == I2C1_Close());
    
}

void LCD_writeNibble(LCD *lcd, uint8_t nibble, uint8_t isCommand) {
    if(isCommand) {
        IO_Expander_write(lcd, nibble << 4 | LCD_EN);
        __delay_us(1);
        IO_Expander_write(lcd, nibble << 4);
        __delay_us(100);
    } else {
        IO_Expander_write(lcd, nibble << 4 | LCD_RS | LCD_EN);
        __delay_us(1);
        IO_Expander_write(lcd, nibble << 4 | LCD_RS);
        __delay_us(100);
    }
}

void LCD_write(LCD *lcd, uint8_t data, uint8_t isCommand) {
    LCD_writeNibble(lcd, data >> 4, isCommand); // first, send the more significant bits
    LCD_writeNibble(lcd, data, isCommand);      // then, send the les significant bits
}

void LCD_init(LCD *lcd, uint8_t address) {
    lcd->address = address;
    lcd->pos = 0;
    lcd->backlight = LCD_BACKLIGHT;
    
    IO_Expander_write(lcd, 0);
    __delay_ms(30);
    
    LCD_writeNibble(lcd, 0x03, 1);
    __delay_ms(5);
    LCD_writeNibble(lcd, 0x03, 1);
    __delay_us(100);
    LCD_writeNibble(lcd, 0x03, 1);
    __delay_ms(5);
    LCD_writeNibble(lcd, 0x02, 1);  // after this line, the LCD driver works in 4 bit mode
    __delay_ms(5);
    
    LCD_write(lcd, 0x28, 1);            // function set: 5x8 dots, 2 lines
    __delay_us(50);
    LCD_write(lcd, LCD_ON_CMD, 1);      // display ON, cursor OFF, blinking OFF
    __delay_us(50);
    LCD_write(lcd, LCD_CLEAR_CMD, 1);   // clear the LCD
    __delay_ms(5);
    LCD_write(lcd, 0x06, 1);            // move the cursor by 1 to the right after data write
    __delay_us(50);
    LCD_write(lcd, LCD_HOME_CMD, 1);    // set the cursor to the upper-left corner
    __delay_ms(5);
}

void LCD_clear(LCD *lcd) {
    LCD_write(lcd, LCD_CLEAR_CMD, 1);
    __delay_ms(5);
}

void LCD_on(LCD *lcd) {
    LCD_write(lcd, LCD_ON_CMD, 1);
}

void LCD_off(LCD *lcd) {
    LCD_write(lcd, LCD_OFF_CMD, 1);
}

void LCD_backlightON(LCD *lcd) {
    lcd->backlight = LCD_BACKLIGHT;
    IO_Expander_write(lcd, 0);
}

void LCD_backlightOFF(LCD *lcd) {
    lcd->backlight = 0;
    IO_Expander_write(lcd, 0);
}

void LCD_home(LCD *lcd) {
    LCD_write(lcd, LCD_HOME_CMD, 1);
    __delay_ms(5);
    lcd->pos = 0;
}

void LCD_setCursor(LCD* lcd, uint8_t row, uint8_t col) {
    if(row < 1 || row > 2 || col < 1 || col > 16) {
        LCD_home(lcd);
    }
    else {
        LCD_write(lcd, 0x80 + ((row == 2) ? 0x40 : 0x00) + col - 1, 1);
        lcd->pos = (row-1)*16 + (col-1);
    }
}

void LCD_printChar(LCD* lcd, char c) {
    if(lcd->pos == 16) {
        LCD_setCursor(lcd, 2, 1);
    }
    LCD_write(lcd, c, 0);
    lcd->data[lcd->pos++] = c;
    lcd->pos %= 32;
    if(lcd->pos == 0) LCD_setCursor(lcd, 1,1);
}

void LCD_printCustomChar(LCD* lcd, uint8_t n) {
    if(lcd->pos == 16) {
        LCD_setCursor(lcd, 2, 1);
    }
    LCD_write(lcd, n, 0);
    lcd->data[lcd->pos++] = n;
    lcd->pos %= 32;
    if(lcd->pos == 0) LCD_setCursor(lcd, 1,1);
}
 
void LCD_print(LCD* lcd, char* str) {
    for(char *cPtr = str; *cPtr != '\0'; cPtr++) {
        LCD_printChar(lcd, *cPtr);
    }
}

void LCD_createCustomChar(LCD *lcd, uint8_t n, uint8_t c[8]) {
    LCD_write(lcd, LCD_SET_CGRAM_ADDR_CMD + 8*n, 1);    // set the CGRAM address
    for(uint8_t i = 0; i < 8; i++) {
        LCD_write(lcd, c[i], 0);                        // write the character data in the CGRAM
    }
    LCD_write(lcd, LCD_HOME_CMD, 1);                    // the next read/write will be again from the DDRAM
}