#include "headers.h"

static BUTTON_Typedef buttons_array[MAX_BUTTONS]= {0};

void Buttons_Initialize( void ) {
    
    memset(buttons_array,0,MAX_BUTTONS);
    
    BUTTON_DIR(OK_BUTTON);
    BUTTON_DIR(FUN_BUTTON);
    BUTTON_DIR(UP_BUTTON);
    BUTTON_DIR(DWN_BUTTON);
}

void Button_Task( void ) {
    
    for(int i = 0; i < MAX_BUTTONS;i++) {
        
        buttons_array[i].state = BUTTON_GET(i);
        
        if(buttons_array[i].state == 0 && !buttons_array[i].pressed) {
            buttons_array[i].pressed = 1;
        }
        
        if(buttons_array[i].pressed && buttons_array[i].state)
        {
            buttons_array[i].pressed = 0;
            buttons_array[i].released = 1;
        }
        
        if(buttons_array[i].released) {
            buttons_array[i].released = 0;
            buttons_array[i].status = 1;
        }
    }
    
    
    
}

uint8_t Button_Get(uint8_t button) {
    uint8_t val = buttons_array[button].status;
    buttons_array[button].status = 0;
    return val;
}
