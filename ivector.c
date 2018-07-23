
#include <htc.h>
#include "main.h"

////////////////////////////////////////////////////
// Прирывание по таймеру 0                        //
// Индикация и временные счетчики                 //
////////////////////////////////////////////////////

void interrupt clock(){
    if (SSPIF)
        SSPOV = SSPIF  = 0;
////////////////////////////////////////////
// Прирывание по таймеру, каждые 0,001 сек.
////////////////////////////////////////////

    if(T0IF){    
////////////////////////////////////////////
// Счетчики времени
//////////////////////////////////////////// 
        uSecond++;
        if(uSecond == 100) {
           uSecond = 0;
           second++;
           if(second == 60) {
               second = 0;
               minute++;
               if (minute == 60) {
                   minute = 0;
                }
            }
        }
    
/////////////////////////////////////////////
// Индикация состояний УКМ
/////////////////////////////////////////////
  
        switch (status) {   
        /////////////////////////////////////////////////
        //Неисправность 
        /////////////////////////////////////////////////

            case ERROR: 
                RELE_E;
                (uSecond < 5 || ( uSecond > 10 && uSecond < 15 ) || ( uSecond > 20 && uSecond < 25)) ? LED_UTECHKA: LED_ALLOFF;
                break;
        /////////////////////////////////////////////////
        //Настройка
        /////////////////////////////////////////////////

            case NASTROYKA:
                RELE_E; 
                (uSecond < 5 || ( uSecond > 10 && uSecond < 15 ) || (uSecond > 20 && uSecond < 25)) ? LED_NORMA: LED_ALLOFF;       
                break;
        /////////////////////////////////////////////////
        //Норма
        /////////////////////////////////////////////////
            case NORMA:
                RELE_N;
                uSecond < 5 ? LED_NORMA: LED_ALLOFF;
                break; 
        /////////////////////////////////////////////////
        //Предутечка
        /////////////////////////////////////////////////
            case PREDUTECHKA: 
                RELE_N;
                uSecond < 5 ? LED_UTECHKA: LED_ALLOFF;
                break;
        /////////////////////////////////////////////////
        //Утечка
        /////////////////////////////////////////////////
            case UTECHKA: 
                RELE_U;
                uSecond < 5 ? LED_UTECHKA: LED_ALLOFF;
                break;
        /////////////////////////////////////////////////
        //Постутечка
        /////////////////////////////////////////////////
            case POSTUTECHKA:
                RELE_U;
                if(uSecond < 5){
                    LED_UTECHKA;
                }else if(uSecond > 5 && uSecond < 95){
                    LED_ALLOFF;
                }else if(uSecond > 95){
                    LED_NORMA;
                }
                break;
        /////////////////////////////////////////////////
        //Неисправность I2C
        /////////////////////////////////////////////////
            case ERRORI2C:
                RELE_E; 
                uSecond < 95 ? LED_NORMA: LED_ALLON;
                break;
        /////////////////////////////////////////////////
        //Неисправность питания УКМ (тензодатчика)
        /////////////////////////////////////////////////
            case ERRORUPIT:
                RELE_E;
                uSecond < 95 ? LED_UTECHKA: LED_ALLON;
                break;

        /////////////////////////////////////////////////
        //Неисправность нет верных данных
        /////////////////////////////////////////////////
            /*case ERROREMI:       
                if (uSecond_emi < 10) {
                    RELE_N;
                    if (uSecond < 5){
                        LED_NORMA;
                    }else{
                        LED_ALLOFF;
                    }
                }else {
                    uSecond_emi = 11;
                    if(uSecond < 5 || ( uSecond > 10 && uSecond < 15 ) || ( uSecond > 20 && uSecond < 25)) {
                        LED_ALLON;
                    }else{
                        LED_UTECHKA;
                    }
                    RELE_N; 
                }       
               break;*/
            default: 
               status = ERRORI2C;
               break;
        }
    }
//if(status != ERROREMI)
  //uSecond_emi == 0;

TMR0 = 99;
T0IF = 0;
INTF = 0;
}

