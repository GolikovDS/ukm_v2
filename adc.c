
#include "adc.h"

//////////////////////////////////////
// Функция чтения внутреннего АЦП МК
//////////////////////////////////////
uint16_t getAdc(){
   GO = 1;	
   while( GO );
   return (ADRESH<<8 | ADRESL);
}


void adcUpit ( void )
{
 int voltageTenzo = 0;
 for (char i = 0;  i < 32; i++ )    
   voltageTenzo += getAdc();
 voltageTenzo >>= 5; 
}

////////////////////////////////////////////////////////////////
// Функция чтения с внешнего АЦП через i2c
// Возвращает результат чтения -1 ошибка 0 данные прочитаны
// Сохраняет результат в значении указателя outData передаваеммого в функцию
////////////////////////////////////////////////////////////////

byte getExternalAdc(uint16_t *outData){
    byte data[3];
    i2cStart();
    if(i2cAddress(WRITE, ADDRESS) == ADC_ERROR)
        return -1;
    if (i2cPutByte(ADC_CONFIG) == ADC_ERROR)
        return -1;
    i2cStop();
    i2cStart();
    if (i2cAddress(READ, ADDRESS) == ADC_ERROR)
        return -1;
    data[0] = i2cGetByte(MORE);                                       //значение данного байта, при наших измерениях, всегда будет 00 и мы его игнорируем
    /*if (data [0] != 0){
     data[0] = data[1] = 0;                                                     //Проверка на обрыв одного проводника 
     return -3;
    }*/
    data[1] = i2cGetByte(MORE); 
    data[2] = i2cGetByte(LAST);
    *outData  = (data[2] << 8) | data[1];
    i2cStop ();

    return 0;
}

byte adcRestart(){
 i2cStart();
 if(i2cAddress(WRITE, ADDRESS) == I2CERROR)
   return I2CERROR;
 if(i2cPutByte (I2CRESET) == I2CERROR)
   return I2CERROR;
 i2cStop();
 return NORMA;
}