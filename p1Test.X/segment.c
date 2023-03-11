#include "headers.h"

    uint8_t cathode_codes[MAX_DIGIT] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x78,0x71,0x40}; 
    
    uint8_t seg_val_1 = 0;
    uint8_t seg_val_2 = 0;
    
    void Segment_Initialize( void ) {
        
        SEGMENT_PORT_DIR = 0xFF;
        SEGMENT_PORT = 0;
        
        SEGMENT_LINE_PORT_DIR |= 0x03;
        SEGMENT_LINE_PORT |= 0;
    }
    
    void Segment_Update(uint8_t s1,uint8_t s2) {
        
        seg_val_1 = s1;
        
        seg_val_2 = s2;
        
    }
    
    void Segment_Task( void ) {
    
        SEGMENT_PORT = 0;
        
        SEGMENT_LINE_PORT &= ~(3 << 0);
        SEGMENT_LINE_PORT |= (1<<1);
        //_delay_us(10);
        SEGMENT_PORT = seg_val_1;
        _delay_ms(2);
         SEGMENT_PORT = 0;
        SEGMENT_LINE_PORT &= ~(3 << 0);
        SEGMENT_LINE_PORT |= (1<<0);
        //_delay_us(10);
        SEGMENT_PORT = seg_val_2;
        _delay_ms(2);
    } 
