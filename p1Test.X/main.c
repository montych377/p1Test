/* 
 * File:   main.c
 * Author: Embedded Web
 *
 * Created on March 11, 2023, 12:56 PM
 */

#include "headers.h"

void  Function_Task( void );
void  Up_Task( void );
void  Down_Task( void );
void  Counter_Task( void );

#define LED1_PIN 2
#define LED1_GND_PIN 3

#define LED1_PORT_DIR DDRC
#define LED1_PORT     PORTC

#define LED1_SET_DIR   ( LED1_PORT_DIR |= (1 << LED1_PIN) )
#define LED1_GND_SET_DIR   ( LED1_PORT_DIR |= (1 << LED1_GND_PIN) )

#define LED1_SET       ( LED1_PORT |= (1 << LED1_PIN) )
#define LED1_CLEAR     ( LED1_PORT &= ~(1 << LED1_PIN) )

#define LED1_GND_SET       ( LED1_PORT |= (1 << LED1_GND_PIN) )
#define LED1_GND_CLEAR     ( LED1_PORT &= ~(1 << LED1_GND_PIN) )

typedef enum {
    IDLE_FUNC,
    TIME_FUNC,
    FREQUNECY_FUNC
}FUN_TYpedef;

typedef struct {

uint8_t freq;
uint8_t time;
uint8_t fun_typ:2;
uint8_t start_counter:1;
}MENU_Typedef;

typedef struct {
    
    uint8_t time;
    uint8_t freq;
    
}EEPROM_Typedef;

MENU_Typedef menu;

EEPROM_Typedef epprom = {.time = 50,.freq = 30};

int main() {
  
    Buttons_Initialize();
    
    Segment_Initialize();
    
    LED1_SET_DIR;
    LED1_GND_SET_DIR;
    
    LED1_CLEAR;
    LED1_GND_CLEAR;
    
    //EEPROM_ReadData(&epprom);
    menu.freq =  epprom.freq;
    menu.time =  epprom.time;
    
    menu.fun_typ = IDLE_FUNC;
    Segment_Update(cathode_codes[menu.time/10],cathode_codes[menu.time%10]);
    LED1_GND_SET;
    while(1) {
        
       if(!menu.start_counter)
       {          
         Button_Task();
       }
       
        Segment_Task();
        
        Function_Task();
        
        Up_Task();
        
        Down_Task();
        
        Counter_Task();
    }
    return (0);
}
uint32_t counts = 0xFF;

void  Function_Task( void ) {
    
    switch(menu.fun_typ) {
        
        case IDLE_FUNC:
            
            if(Button_Get(OK_BUTTON)) {
              
               menu.start_counter = 1;
               counts =  0xFF;
               LED1_SET;
               LED1_GND_CLEAR;
            }
            if(Button_Get(FUN_BUTTON)) {
               menu.fun_typ =  TIME_FUNC;
               Segment_Update(cathode_codes[DIGIT_t],cathode_codes[DIGIT_d]);
            }            
            break;
            
        case TIME_FUNC:
            if(Button_Get(OK_BUTTON)) {
                menu.fun_typ =  FREQUNECY_FUNC;
               Segment_Update(cathode_codes[DIGIT_f],cathode_codes[DIGIT_d]);
            }
            break;
            
        case FREQUNECY_FUNC:
            if(Button_Get(OK_BUTTON)) {
                menu.fun_typ =  IDLE_FUNC;
                
                epprom.time = menu.time;
                epprom.freq = menu.freq;
                
                //EEPROM_WriteData(&epprom);
               Segment_Update(cathode_codes[menu.time/10],cathode_codes[menu.time%10]);
            }
            break;
        
    }
}

void  Up_Task( void ) {

    if( menu.fun_typ != IDLE_FUNC) {
        if(Button_Get(UP_BUTTON)) {
            
            if(menu.fun_typ ==  TIME_FUNC && menu.time < 100) { 
                menu.time++;
                Segment_Update(cathode_codes[menu.time/10],cathode_codes[menu.time%10]);
            }
            
            if(menu.fun_typ ==  FREQUNECY_FUNC && menu.freq < 30) { 
                menu.freq++;
                Segment_Update(cathode_codes[menu.freq/10],cathode_codes[menu.freq%10]);
            }
        }
    }
}

void  Down_Task( void ) {

    if( menu.fun_typ != IDLE_FUNC) {
        
        if(Button_Get(DWN_BUTTON)) {
            
            if(menu.fun_typ ==  TIME_FUNC && menu.time ) { 
                menu.time--;
                Segment_Update(cathode_codes[menu.time/10],cathode_codes[menu.time%10]);
            }
            
            if(menu.fun_typ ==  FREQUNECY_FUNC && menu.freq) { 
                menu.freq--;
                Segment_Update(cathode_codes[menu.freq/10],cathode_codes[menu.freq%10]);
            }
        }
    }
}

void  Counter_Task( void ) {
   
    if(menu.start_counter){
        
        if(counts) {
            counts--;
            return;
        }
        
        if(menu.time) {
              counts =  0xFF;
               menu.time--;
              Segment_Update(cathode_codes[menu.time/10],cathode_codes[menu.time%10]);
             
        }else {
            menu.start_counter = 0;
            menu.time = epprom.time;
            Segment_Update(cathode_codes[menu.time/10],cathode_codes[menu.time%10]);
            
        }
    }
}