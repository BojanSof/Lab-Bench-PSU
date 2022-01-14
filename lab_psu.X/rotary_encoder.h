/* 
 * File:   rotary_encoder.h
 * Author: Bojan Sofronievski
 *
 * Created on September, 18 2021, 16:08
 */

#ifndef ROTARY_ENCODER_H
#define	ROTARY_ENCODER_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * \brief Determine if the encoder was turned CW or CCW
 *
 * \return 1 for CW, -1 for CCW and 0 for invalid movement
 */
int8_t RotaryEncoder_read(void);

/**
 * \brief Determine if the button was pressed
 *
 * \return Nothing
 */
void RotaryEncoder_button(void);

#ifdef	__cplusplus
}
#endif

#endif	/* ROTARY_ENCODER_H */

