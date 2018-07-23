/* 
 * File:   i2c.h
 * Author: user145
 *
 * Created on 18 июля 2018 г., 10:47
 */

#ifndef I2C_H
#define	I2C_H
#include "util.h"
#include "main.h"

#define ADDRESS      0b1101000
#define ADDRESSMON   0b00111000
#define MORE         0
#define LAST         1
#define WRITE        0
#define READ         1
#define I2CCONFIG    0x9F
#define I2CRESET     0x06
#define I2CERROR     27
#define I2C_DELAY    1
#define BREAKTOLOOP  60000


char i2cStart ( void );
void CheckSspif ( void );
char i2cStop ( void );
char i2cAddress (  char , char   );
char i2cPutByte ( char );
char i2cGetByte ( char );
char i2cReStart( void );
char breakToLoop ( void );

unsigned int counti2cloop = 0;
#endif	/* I2C_H */

