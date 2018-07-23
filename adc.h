/* 
 * File:   adc.h
 * Author: user145
 *
 * Created on 18 июля 2018 г., 9:19
 */

#ifndef ADC_H
#define	ADC_H
#include <htc.h>
#include <stdint.h>
#include "i2c.h"



#define ADDRESS      0b1101000
#define ADC_CONFIG    0x9F
#define ADC_RESET     0x06
#define ADC_ERROR     27
#define MORE         0
#define LAST         1


uint16_t getAdc();
void adcUpit ( void );
byte getExternalAdc(uint16_t *outData);
byte adcRestart();
#endif	/* ADC_H */

