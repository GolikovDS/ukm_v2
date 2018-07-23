
#include "eeprom.h"

///////////////////////////////////
//Запись  в  EERUM               
///////////////////////////////////

void saveMemori (byte address, byte data){
    EEADR = address;
    EEDATA = data;
    WREN = 1;
    GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    WR = 1;
    WREN = 0;
    while (WR);
    GIE = 1;	
}

/////////////////////////////////
//Чтение из EERUM              
/////////////////////////////////

byte readMemori (byte address){
    GIE = 0;
    EEADR = address;
    RD = 1;
    byte memdata = EEDATA;
    GIE = 1;
    return memdata;
}

