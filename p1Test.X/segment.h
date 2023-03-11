/* 
 * File:   segment.h
 * Author: Embedded Web
 *
 * Created on March 11, 2023, 1:21 PM
 */

#ifndef SEGMENT_H
#define	SEGMENT_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>

#define SEGMENT_PORT_DIR DDRD
#define SEGMENT_PORT PORTD
#define SEGMENT_LINE_PORT_DIR DDRC
#define SEGMENT_LINE_PORT PORTC

    typedef enum {
        DIGIT_0,
        DIGIT_1,
        DIGIT_2,
        DIGIT_3,
        DIGIT_4,
        DIGIT_5,
        DIGIT_6,
        DIGIT_7,
        DIGIT_8,
        DIGIT_9,
        DIGIT_t,
        DIGIT_f,
        DIGIT_d,
        MAX_DIGIT
    } DIGIT_Typedef;
    
    extern uint8_t cathode_codes[MAX_DIGIT];
    
    void Segment_Update(uint8_t s1,uint8_t s2);
    void Segment_Initialize(void);
    void Segment_Task(void);


#ifdef	__cplusplus
}
#endif

#endif	/* SEGMENT_H */

