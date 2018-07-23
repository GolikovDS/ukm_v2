/* 
 * File:   main.c
 * Author: golikov.d.s@yandex.ru
 *
 * Created on 17 июля 2018 г., 10:19
 */

#include <stdio.h>
#include <stdlib.h>
#include <htc.h>

#include "util.h"
#include "main.h"
#include "uart.h"
#include "adc.h"
#include "i2c.h"
__CONFIG (0x2BB4);
__CONFIG (0x3FFF);


void init (){
    TRISA = 0b01111111;
    TRISB = 0b00010000;
    TRISC = 0b11011000;
    PORTA = 0b00000000;
    PORTB = 0b00000000;
    PORTC = 0b00000000;

    ANSELH = 0;
    WPUB = 1;
    IOCB = 0;
    ANSEL = 1;
 
    ADCON0 = 0b10000001;
    ADCON1 = 0b10110000;                     
    ADON=1;	

    OSCCON = 0b01100101;
    OPTION_REG = 0b10000101;

    INTCON = 0b00100000;

    GIE = 0;
    TMR0 = 96;
    //i2c//
    SSPADD = 103;                            //4 MГц осцилятор и скорость и2с 9600 
    SSPIF = 0;
    SSPSTAT = 0b00000000;
    SSPCON = 0b00111000;
    SSPCON2 = 0b00000000; 
    adcRestart();
}
int main(int argc, char** argv) {

    init();
    GIE = 1;
    status = NORMA;
    TENZO_ON;
    
    while(TRUE){
        for(int i = 0; i < 20; i++)
            __delay_ms(20);
        
      
            DeviceData.innerAdc.value = getAdc();        
            
            getExternalAdc(&DeviceData.externalAdc.value);
            pushByte(DeviceData.externalAdc.toByte[0]);
            pushByte(DeviceData.externalAdc.toByte[1]);

        
    }
   
    return (EXIT_SUCCESS);
}

