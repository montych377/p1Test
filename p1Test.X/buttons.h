/* 
 * File:   buttons.h
 * Author: Embedded Web
 *
 * Created on March 11, 2023, 12:57 PM
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
    
    typedef enum {
    
        OK_BUTTON = 0,
        FUN_BUTTON,
        UP_BUTTON,
        DWN_BUTTON,
        MAX_BUTTONS
                
    }BUTTONS_ENUM_Typedef;
    
    typedef struct {
        uint8_t state:1;
        uint8_t pressed:1;
        uint8_t released:1;
        uint8_t status:1;
        uint8_t :4;
    }BUTTON_Typedef;
    
#define BUTTONS_PORT_DIR DDRB
#define BUTTONS_PORT     PORTB
    
#define BUTTON_DIR(x) (DDRB = (0 << x))   
#define BUTTON_GET(x) ((PINB & (1 << x)) ? 1 : 0) 

    
void Buttons_Initialize( void );
void Button_Task( void );
uint8_t Button_Get(uint8_t button);
    
#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

