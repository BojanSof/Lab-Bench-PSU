/* 
 * File:   psu.h
 * Author: bojan
 *
 * Created on September 28, 2021, 3:58 PM
 */

#ifndef PSU_H
#define	PSU_H

#include <pic.h>
#include "lcd.h"
#include "rotary_encoder.h"
#include "mcc_generated_files/pwm1.h"

// PSU states
typedef enum PSUstate {
    STATE_OFF_VOLTAGE,
    STATE_OFF_CURRENT,
    STATE_OFF_ADJUSTMENT,
    STATE_OFF_ON_BTN,
    STATE_OFF_VOLTAGE_SELECTED,
    STATE_OFF_CURRENT_SELECTED,
    STATE_OFF_ADJUSTMENT_SELECTED,
    STATE_ON_VOLTAGE,
    STATE_ON_CURRENT,
    STATE_ON_ADJUSTMENT,
    STATE_ON_ON_BTN,
    STATE_ON_VOLTAGE_SELECTED,
    STATE_ON_CURRENT_SELECTED,
    STATE_ON_ADJUSTMENT_SELECTED,
} PSUstate;

#define STATE_OFF_BOUND     6

// Adjustments
#define FINE_ADJUSTMENT     0
#define COARSER_ADJUSTMENT  1
#define COARSE_ADJUSTMENT   2
#define NUM_ADJUSTMENTS     3
#define FINE_VOLTAGE        15  // mV
#define FINE_VOLTAGE_UV     14648U  // uV
#define FINE_CURRENT        5   // mA
#define FINE_CURRENT_UV     4883U   // uV
#define COARSER_VOLTAGE     45  // mV
#define COARSER_CURRENT     50  // mA
#define COARSE_VOLTAGE      105 // mV
#define COARSE_CURRENT      100 // mA

// Function aliases
#define PSU_setVoltageDutyCycle(dutyCycle) PWM1_LoadDutyValue(dutyCycle)
#define PSU_setCurrentLimitDutyCycle(dutyCycle) PWM2_LoadDutyValue(dutyCycle)

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef struct PSU {    
    uint16_t voltage;      // the voltage, in mV
    uint16_t current;      // the current in mA
    
    uint16_t voltageSet;   // the voltage requested by the user, in mV
    uint16_t currentLimit; // the current limit, in mA
    
    uint16_t voltageStep;
    uint16_t currentLimitStep;
    
    uint16_t maxVoltage;    // max voltage output
    uint16_t maxCurrent;    // max current
    
    PSUstate state;
    uint8_t adjustment;     //0->fine adjustment, 1->coarser adjustment, 2->coarse adjustment
    
    LCD *lcd;           // pointer to LCD instance
} PSU;

/**
 * \brief Initialize the PSU
 *
 * \param[in] psu Pointer to PSU instance
 *
 * \return Nothing
 */
void PSU_init(volatile PSU *psu, LCD *lcd, uint8_t lcdAddress, uint16_t maxVoltage, uint16_t maxCurrent);

/**
 * \brief Measure the actual voltage on the output
 *
 * \param[in] psu Pointer to PSU instance
 *
 * \return Nothing
 */
void PSU_measureVoltage(volatile PSU *psu);

/**
 * \brief Measure the current
 *
 * \param[in] psu Pointer to PSU instance
 *
 * \return Nothing
 */
void PSU_measureCurrent(volatile PSU *psu);

/**
 * \brief Update the measurements (voltage and current)
 *
 * \param[in] psu Pointer to PSU instance
 *
 * \return Nothing
 */
void PSU_updateMeasurements(volatile PSU *psu);

/**
 * \brief Update the LCD with the PSU status
 *
 * \param[in] psu Pointer to PSU instance
 *
 * \return Nothing
 */
void PSU_updateLCD(volatile PSU *psu);

/**
 * \brief Update the state of the PSU
 *
 * \param[in] psu Pointer to PSU instance
 * \param[in] rotEncVal The direction of the change of the rotary encoder
 *
 * \return Nothing
 */
void PSU_update(volatile PSU *psu, int8_t rotEncVal);

#ifdef	__cplusplus
}
#endif

#endif	/* PSU_H */

