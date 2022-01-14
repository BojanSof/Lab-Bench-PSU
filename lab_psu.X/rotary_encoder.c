#include "rotary_encoder.h"
#include "mcc_generated_files/mcc.h"
#include "utility.h"

extern volatile uint8_t change;

int8_t RotaryEncoder_read(void) {
    /* The rotary encoder movements are gray coded
     * The state of the rotary encoder is represented with two bits,
     * the msb is the state of the DATA pin and the lsb is the state of the CLK
     * pin.
     * e.g. if the previous code was 0b00, for CW movement, the new code should 
     * be 0b01 and 0b10 for CCW movement; therefore, the values in the table at 
     * indices 0b0001=1 and 0b0010=2 have value 1, standing for possible state,
     * but the values at indices 0b0000=0 and 0b0011=3 have value 0, meaning
     * that the state is impossible
     *                              CCW   |   CW
     *                         <-------------------->
     * States during movement: 11<->10<->00<->01<->11
     *                                   ^^-- starting point
     */
    static uint8_t rotaryEncoderTable[] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};
    static uint8_t prevNextCode = 0; // the index for the table
    static uint16_t store = 0;       // for double (or max quadruple) debouncing
    
    prevNextCode <<= 2;
    if(RotEncCLK_GetValue()) prevNextCode |= 0x01;
    if(RotEncDT_GetValue()) prevNextCode |= 0x02;
    prevNextCode &= 0x0F;

     // If the current movement is valid, store it
     if(rotaryEncoderTable[prevNextCode] ) {
        store <<= 4;
        store |= prevNextCode;
        if ((store & 0xFF) == 0x2B) {
            change = ROTARY_ENCODER_CHANGE;
            return -1;
        }
        if ((store & 0xFF) == 0x17) {
            change = ROTARY_ENCODER_CHANGE;
            return 1;
        }
     }
     return 0;
}

void RotaryEncoder_button(void) {
    static uint16_t state = 0;
    static uint8_t pressed = 0;
    state = (state << 1) | RotEncSW_GetValue() | 0xFFF0;
    if(state == 0xFFF0) {
        if(!pressed) {
            pressed = 1;
            change = BUTTON_CHANGE;
        }
    } else {
        pressed = 0;
    }
}