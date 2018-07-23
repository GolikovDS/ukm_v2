#include <htc.h>
#include "i2c.h"


///////////////////////////////////////////
// I2C аппаратная реализация
//////////////////////////////////////////

byte breakToLoop(){
 if (counti2cloop == BREAKTOLOOP)
   return I2CERROR;
  return 1;
}
//////////////////////////////////////////
//Старт
//////////////////////////////////////////
byte i2cStart(){
 counti2cloop = 0;
 SEN = 1;
 while(SEN){
   counti2cloop++;
   if(breakToLoop() == I2CERROR) {
     counti2cloop = 0;
     return I2CERROR;
   }
 }
 CheckSspif();
 __delay_ms (I2C_DELAY);
 return TRUE;
}

////////////////////////////////////////////
///Рестарт
////////////////////////////////////////////
/**
char 
i2cReStart( void )
{
 RSEN = 1;
 while( RSEN ); 
 CheckSspif();

 __delay_ms ( I2C_DELAY );

}
*/
//////////////////////////////////////////
//Стоп
//////////////////////////////////////////

char i2cStop(void){
 counti2cloop = 0;
 PEN = 1;
 while( PEN ) {
   counti2cloop++;
   if ( breakToLoop () == I2CERROR ) {
     counti2cloop = 0;
     return I2CERROR;
   }
 } 
 CheckSspif();
 __delay_us (I2C_DELAY);
 return 1;
}

///////////////////////////////////////////
//Сброс флага SSPOV
///////////////////////////////////////////

void CheckSspif(void){ 
 SSPOV = SSPIF = 0;
}

//////////////////////////////////////////////
//WRITE-запись, READ-чтение, MORE-чтение 
//продолжается (не последний байт в передачи)
//LAST-последний принемаемый байт
//Пример:
//
//  i2cStart();     
//  status = i2cAddress(WRITE);
//  status = i2cPutByte (123);
//  i2cStop();
// 
//  i2cStart();
//  status = i2cAddress(READ);
//  char i = i2cGetByte (MORE);
//  char s = i2cGetByte (LAST);
//  i2cStop();
//
//////////////////////////////////////////////

//////////////////////////////////////////////
//Функция вызыва устройства по адресу с
//указанием настройки на чтения или запись 
//(WRITE, READ)
//////////////////////////////////////////////

char i2cAddress(char w_r, char address){
 counti2cloop = 0;
 /*if(w_r == WRITE){ 
   w_r = 0;
 }else{
   w_r = 1;
 } */
 SSPBUF = (address << 1) | w_r; 
 while(BF){
   counti2cloop++;
   if (breakToLoop() == I2CERROR){
     counti2cloop = 0;
     return I2CERROR;
   }
 }  
 CheckSspif(); 
  __delay_ms (I2C_DELAY); 
 if (ACKSTAT == 0){ 
   return NORMA; 
 }   
 return I2CERROR;
}

///////////////////////////////////////////////
//Функция отправки байта
///////////////////////////////////////////////

char i2cPutByte(char bytes){ 
 counti2cloop = 0;
 SSPBUF = bytes;
 while( BF ) {
   counti2cloop++;
   if ( breakToLoop () == I2CERROR ){
     counti2cloop = 0;
     return I2CERROR;
   }
 }   
 CheckSspif();
 __delay_ms (I2C_DELAY);
 if (ACKSTAT == 0)  
   return NORMA;	
 return ERROR; 
}

//////////////////////////////////////////////////
//Функция получения байта, с указанием на то что
//полученный байт является последним (LAST) или
//байт не последний (MORE)
//////////////////////////////////////////////////

char 
i2cGetByte(char ack)
{
 counti2cloop = 0;
 char data;
 RCEN = 1;
 while( RCEN ) {
   counti2cloop++;
   if ( breakToLoop () == I2CERROR ){
     counti2cloop = 0;
     return I2CERROR;
   }
 }   
 data = SSPBUF;
 while(BF) {
   counti2cloop++;
   if ( breakToLoop () == I2CERROR ) {
     counti2cloop = 0;
     return I2CERROR;
   }
 }   
 CheckSspif();
 if(!ack) {
   ACKDT = 0;
   ACKEN = 1;
 }else{
   ACKDT = 1;
   ACKEN = 1;
 } 
 __delay_ms (I2C_DELAY);
 return data; 
}