#include "psu.h"
#include "mcc_generated_files/mcc.h"
#include "utility.h"

// custom characters numbers
#define OFF_SYMBOL              0
#define OFF_SYMBOL_SELECTED     1
#define ON_SYMBOL               2
#define ON_SYMBOL_SELECTED      3
#define COARSE_SYMBOL           4
#define COARSER_SYMBOL          5
#define FINE_SYMBOL             6

extern volatile uint8_t change;

void PSU_init(volatile PSU *psu, LCD *lcd, uint8_t lcdAddress, uint16_t maxVoltage, uint16_t maxCurrent) {
    psu->maxVoltage = maxVoltage;
    psu->maxCurrent = maxCurrent;
    
    psu->voltageStep = FINE_VOLTAGE;       // 10 bit PWM resolution, gain=3
    psu->currentLimitStep = FINE_CURRENT;  // 10 bit PWM resolution
    
    psu->voltageSet = psu->currentLimit = 0;
    
    psu->adjustment = 0;
    psu->state = 0;
    
    //Initialize the LCD
    psu->lcd = lcd;
    LCD_init(psu->lcd, lcdAddress);
    // create custom characters, for on/off and coarse/fine adjustment
    uint8_t customChar[8];
    // off symbol
    customChar[0] = 0b00000000;
    customChar[1] = 0b00001110;
    customChar[2] = 0b00010001;
    customChar[3] = 0b00010001;
    customChar[4] = 0b00010001;
    customChar[5] = 0b00010001;
    customChar[6] = 0b00001110;
    customChar[7] = 0b00000000;
    LCD_createCustomChar(lcd, OFF_SYMBOL, customChar);
    // off symbol, selected
    customChar[0] = 0b00011111;
    customChar[1] = 0b00010001;
    customChar[2] = 0b00001110;
    customChar[3] = 0b00001110;
    customChar[4] = 0b00001110;
    customChar[5] = 0b00001110;
    customChar[6] = 0b00010001;
    customChar[7] = 0b00011111;
    LCD_createCustomChar(lcd, OFF_SYMBOL_SELECTED, customChar);
    // on symbol
    customChar[0] = 0b00000000;
    customChar[1] = 0b00000100;
    customChar[2] = 0b00000100;
    customChar[3] = 0b00000100;
    customChar[4] = 0b00000100;
    customChar[5] = 0b00000100;
    customChar[6] = 0b00000100;
    customChar[7] = 0b00000000;
    LCD_createCustomChar(lcd, ON_SYMBOL, customChar);
    // on symbol, selected
    customChar[0] = 0b00011111;
    customChar[1] = 0b00011011;
    customChar[2] = 0b00011011;
    customChar[3] = 0b00011011;
    customChar[4] = 0b00011011;
    customChar[5] = 0b00011011;
    customChar[6] = 0b00011011;
    customChar[7] = 0b00011111;
    LCD_createCustomChar(lcd, ON_SYMBOL_SELECTED, customChar);
    // coarse adjustment
    customChar[0] = 0b00010000;
    customChar[1] = 0b00000010;
    customChar[2] = 0b00000000;
    customChar[3] = 0b00001000;
    customChar[4] = 0b00000000;
    customChar[5] = 0b00000001;
    customChar[6] = 0b00000000;
    customChar[7] = 0b00000100;
    LCD_createCustomChar(lcd, COARSE_SYMBOL, customChar);
    // coarser adjustment
    customChar[0] = 0b00010001;
    customChar[1] = 0b00000000;
    customChar[2] = 0b00001001;
    customChar[3] = 0b00010000;
    customChar[4] = 0b00000010;
    customChar[5] = 0b00001000;
    customChar[6] = 0b00000000;
    customChar[7] = 0b00010001;
    LCD_createCustomChar(lcd, COARSER_SYMBOL, customChar);
    // fine adjustment
    customChar[0] = 0b00010101;
    customChar[1] = 0b00001010;
    customChar[2] = 0b00010101;
    customChar[3] = 0b00001010;
    customChar[4] = 0b00010101;
    customChar[5] = 0b00001010;
    customChar[6] = 0b00010101;
    customChar[7] = 0b00001010;
    LCD_createCustomChar(lcd, FINE_SYMBOL, customChar);
    
    PSU_updateLCD(psu);
}

void PSU_measureVoltage(volatile PSU *psu) {
    ADCC_DischargeSampleCapacitor();
    uint16_t val = ADCC_GetSingleConversion(Vout);
    psu->voltage = ((uint32_t)val*15000U)/1024;
}

void PSU_measureCurrent(volatile PSU *psu) {
    ADCC_DischargeSampleCapacitor();
    uint16_t val = ADCC_GetSingleConversion(Iout);
    psu->current = ((uint32_t)val*5000U)/1024;
}

void PSU_updateMeasurements(volatile PSU *psu) {
    PSU_measureVoltage(psu);
    PSU_measureCurrent(psu);
}

void PSU_updateLCD(volatile PSU *psu) {
    static char buffer[16];
    LCD_clear(psu->lcd);
    LCD_home(psu->lcd);
    // print the voltage in the first row
    if( psu->state <= STATE_OFF_BOUND ||
        psu->state == STATE_ON_VOLTAGE ||
        psu->state == STATE_ON_VOLTAGE_SELECTED ) {
        sprintf(buffer, " %2hu.%03hu V", wholePart(psu->voltageSet), decimalPart(psu->voltageSet));
    }
    else {
        sprintf(buffer, " %2hu.%03hu V", wholePart(psu->voltage), decimalPart(psu->voltage));
    }
    LCD_print(psu->lcd, buffer);
    // print the current in the second row
    LCD_setCursor(psu->lcd, 2, 1);
    if( psu->state <= STATE_OFF_BOUND ||
        psu->state == STATE_ON_CURRENT || 
        psu->state == STATE_ON_CURRENT_SELECTED ) {
        sprintf(buffer, " %2hu.%03hu A", wholePart(psu->currentLimit), decimalPart(psu->currentLimit));
    }
    else {
        sprintf(buffer, " %2hu.%03hu A", wholePart(psu->current), decimalPart(psu->current));
    }
    LCD_print(psu->lcd, buffer);
    // print the adjustment symbol at the end of the first row
    LCD_setCursor(psu->lcd, 1, 16);
    if(psu->adjustment == FINE_ADJUSTMENT) {
        LCD_printCustomChar(psu->lcd, FINE_SYMBOL);
    } else if(psu->adjustment == COARSER_ADJUSTMENT) {
        LCD_printCustomChar(psu->lcd, COARSER_SYMBOL);
    } else {
        LCD_printCustomChar(psu->lcd, COARSE_SYMBOL);
    }
    // print on symbol at the end of the second row if psu is on, off symbol otherwise
    LCD_setCursor(psu->lcd, 2, 16);
    if(psu->state > STATE_OFF_BOUND) {
        if(psu->state == STATE_ON_ON_BTN)
            LCD_printCustomChar(psu->lcd, ON_SYMBOL_SELECTED);
        else
            LCD_printCustomChar(psu->lcd, ON_SYMBOL);
    } else {
        if(psu->state == STATE_OFF_ON_BTN)
            LCD_printCustomChar(psu->lcd, OFF_SYMBOL_SELECTED);
        else
            LCD_printCustomChar(psu->lcd, OFF_SYMBOL);
    }
    // print the selection indicator
    if( psu->state == STATE_OFF_VOLTAGE ||
        psu->state == STATE_OFF_VOLTAGE_SELECTED ||
        psu->state == STATE_ON_VOLTAGE ||
        psu->state == STATE_ON_VOLTAGE_SELECTED ) {
        
        LCD_setCursor(psu->lcd, 1, 1);
        LCD_printChar(psu->lcd, '>');
    } else if( psu->state == STATE_OFF_CURRENT ||
        psu->state == STATE_OFF_CURRENT_SELECTED ||
        psu->state == STATE_ON_CURRENT ||
        psu->state == STATE_ON_CURRENT_SELECTED ) {
        
        LCD_setCursor(psu->lcd, 2, 1);
        LCD_printChar(psu->lcd, '>');
    } else if( psu->state == STATE_OFF_ADJUSTMENT ||
        psu->state == STATE_OFF_ADJUSTMENT_SELECTED ||
        psu->state == STATE_ON_ADJUSTMENT ||
        psu->state == STATE_ON_ADJUSTMENT_SELECTED ) {
        
        LCD_setCursor(psu->lcd, 1, 15);
        LCD_printChar(psu->lcd, '>');
    }
}

void PSU_update(volatile PSU *psu, int8_t rotEncVal) {
    if(change == ROTARY_ENCODER_CHANGE) {
        switch(psu->state) {
            // Selecting different entities in the menu
            case STATE_OFF_VOLTAGE:
            case STATE_OFF_CURRENT:
            case STATE_OFF_ADJUSTMENT:
            case STATE_OFF_ON_BTN:
                psu->state = (psu->state + rotEncVal) % 4;
            break;
            case STATE_ON_VOLTAGE:
            case STATE_ON_CURRENT:
            case STATE_ON_ADJUSTMENT:
            case STATE_ON_ON_BTN:
                psu->state = STATE_ON_VOLTAGE + (psu->state - STATE_ON_VOLTAGE + rotEncVal) % 4;
            break;
            // Changing voltage value
            case STATE_OFF_VOLTAGE_SELECTED:
            case STATE_ON_VOLTAGE_SELECTED:
                psu->voltageSet = psu->voltageSet + rotEncVal * psu->voltageStep;
                if(psu->voltageSet > 65400) psu->voltageSet = psu->maxVoltage;
                else if(psu->voltageSet > psu->maxVoltage) psu->voltageSet = 0;
            break;
            // Changing current limit value
            case STATE_OFF_CURRENT_SELECTED:
            case STATE_ON_CURRENT_SELECTED:
                psu->currentLimit = psu->currentLimit + rotEncVal * psu->currentLimitStep;
                if(psu->currentLimit > 65400) psu->currentLimit = psu->maxCurrent;
                else if(psu->currentLimit > psu->maxCurrent) psu->currentLimit = 0;
            break;
            // Changing step values
            case STATE_OFF_ADJUSTMENT_SELECTED:
            case STATE_ON_ADJUSTMENT_SELECTED:
                psu->adjustment = psu->adjustment + rotEncVal;
                if(psu->adjustment == 255) psu->adjustment = 2;
                else if(psu->adjustment >= NUM_ADJUSTMENTS) psu->adjustment = 0;
            break;
            default:
            break;
        }
    } else if(change == BUTTON_CHANGE) {
        switch(psu->state) {
            // switch to value changing state
            case STATE_OFF_VOLTAGE:
            case STATE_OFF_CURRENT:
            case STATE_OFF_ADJUSTMENT:
            case STATE_ON_VOLTAGE:
            case STATE_ON_CURRENT:
            case STATE_ON_ADJUSTMENT:
                psu->state += 4;
            break;
            // switch to menu entry selection state
            case STATE_OFF_VOLTAGE_SELECTED:
            case STATE_OFF_CURRENT_SELECTED:
                psu->state -= 4;
            break;
            case STATE_OFF_ADJUSTMENT_SELECTED:
            case STATE_ON_ADJUSTMENT_SELECTED:    
                switch(psu->adjustment) {
                    case FINE_ADJUSTMENT:
                        psu->voltageStep = FINE_VOLTAGE;
                        psu->currentLimitStep = FINE_CURRENT;
                    break;
                    case COARSER_ADJUSTMENT:
                        psu->voltageStep = COARSER_VOLTAGE;
                        psu->currentLimitStep = COARSER_CURRENT;
                    break;
                    case COARSE_ADJUSTMENT:
                        psu->voltageStep = COARSE_VOLTAGE;
                        psu->currentLimitStep = COARSE_CURRENT;
                    break;
                    default:
                    break;
                }
                psu->state -= 4;
            break;
            // update the pwm signal duty cycle
            case STATE_ON_VOLTAGE_SELECTED:
                psu->state -= 4;
                PSU_setVoltageDutyCycle((((uint32_t)psu->voltageSet)*1000U)/FINE_VOLTAGE_UV);
            break;
            case STATE_ON_CURRENT_SELECTED:
                psu->state -= 4;
                //PSU_setCurrentLimitDutyCycle(((uint32_t)psu->currentLimit)*1000U/FINE_CURRENT_UV);
            break;
            // switch the PSU to the ON state
            case STATE_OFF_ON_BTN:
                psu->state = STATE_ON_ON_BTN;
                // enable PWM signals
                PSU_setVoltageDutyCycle((((uint32_t)psu->voltageSet)*1000U)/FINE_VOLTAGE_UV);
                //PSU_setCurrentLimitDutyCycle((((uint32_t)psu->currentLimit)*1000U)/FINE_CURRENT_UV);
            break;
            // switch the PSU to the OFF state
            case STATE_ON_ON_BTN:
                psu->state = STATE_OFF_ON_BTN;
                // disable PWM signals
                PSU_setVoltageDutyCycle(0);
                //PSU_setCurrentLimitDutyCycle(0);
            break;
            default:
            break;
        }
    } else if(change == MEASUREMENTS_CHANGE) {
        PSU_updateMeasurements(psu);
    }
    if(change) {
        PSU_updateLCD(psu);
        change = NO_CHANGE;
    }
        
}