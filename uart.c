
#include "uart.h"


void pushByte(byte b){
    GIE = FALSE;
    /*************START BIT********************************/
    CLEAR_TX;
    __delay_us(TIMEOUT);
    /******************************************************/
    /*********************DATA*****************************/
    for(int i = 0; i < 8; i++){
        if(b & 0x01)
            SET_TX;
        else
            CLEAR_TX;
        __delay_us(TIMEOUT);               
        b >>= 1;
    }
    /******************************************************/
    /*****************STOP BIT*****************************/
    SET_TX;
    __delay_us(TIMEOUT); 
    /******************************************************/
    //freeLine();
    GIE = TRUE;
}

void pushString(char* str, byte lenght){
    for(int i = 0; i < lenght; i++){
        pushByte(str[i]);
    }
}
