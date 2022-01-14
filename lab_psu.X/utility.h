/* 
 * File:   utility.h
 * Author: bojan
 *
 * Created on October 3, 2021, 6:44 PM
 */

#ifndef UTILITY_H
#define	UTILITY_H

// Change states
#define NO_CHANGE               0
#define ROTARY_ENCODER_CHANGE   1
#define BUTTON_CHANGE           2
#define MEASUREMENTS_CHANGE     3

// for converting mV in V and mA in A
#define wholePart(n) n/1000
#define decimalPart(n) n - n/1000*1000

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* UTILITY_H */

