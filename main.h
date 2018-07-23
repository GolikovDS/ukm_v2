/* 
 * File:   main.h
 * Author: user145
 *
 * Created on 17 июля 2018 г., 11:48
 */

#ifndef MAIN_H
#define	MAIN_H
#include <stdint.h>
#define _XTAL_FREQ   4000000                           //Частота работы микроконтроллера УКМ


/////////////////////////////////
//Состояние УКМ
/////////////////////////////////
#define SETTING      RB4                               //Настройка
#define ERROR        0                                 //Неисправность (масса больше или меньше допустимых значений см. MINMASS и MAXMASS)
#define NORMA        1                                 //Норма (масса в пределе допустимых значений и больше порога утечки)
#define PREDUTECHKA  3                                 //Предутечка(масса в пределе допустимых значений но меньше порога утечки и утечка произошла недавно (менее пяти циклов измерений). 
                                                       //Есть возможность вернуться в норму) Реле не переключилось в утечку, но индикация утечки
#define UTECHKA      2                                 //Утечка (масса в пределе допустимых значений но меньше порога утечки. Утечка зафиксирована более пяти циклов измерений назад)
#define POSTUTECHKA  4                                 //Постутечка (масса в пределе допустимых значений и больше порога утечки, но до этого было состояние утечка.)
                                                       //Реле остается в состоянии утечка, индикация меняется на соответсвующию
#define ERRORI2C     5                                 //Ошибка данных шины I2C (внешний АЦП не отвечает)
#define ERRORUPIT    6                                 //Ошибка питания (напряжение питания тензодатчика ниже допустимых значений см. MINUPIT и MAXUPIT)
#define NASTROYKA    7                                 //Настройка (состояние настройки УКМ)
#define ERROREMI     8                                 //Ошибка получаемых данных от внешнего АЦП(не удалось получить подряд 7 одинаковых данных с допуском см. KOEFDOPOTKL, за 30 циклов измерения)
#define ERROREMI_OLD 9                                 //Включае неисправность на 10 цикле

//////////////////////////////////
//Индикация УКМ
//////////////////////////////////
#define LED_ALLOFF   RB0 = 0, RB1 = 0                     //Оба светодиода отключены
#define LED_NORMA    RB0 = 1, RB1 = 0                  //Зеленый горит красный не горит
#define LED_UTECHKA  RB0 = 0, RB1 = 1                  //Зеленый не горит красный горит
#define LED_ALLON    RB0 = 1, RB1 = 1                     //Оба светодиода горят
//////////////////////////////////
//Питание тензодатчика
//////////////////////////////////
#define TENZO_ON     RA7 = 1                           //Подать питание на тензодатчик
#define TENZO_OFF    RA7 = 0                           //Отключить питание тензодатчика
//////////////////////////////////
//Переключение реле
//////////////////////////////////
#define RELE_N       RB2 = 1, RB3 = 0                  //Включить реле норма, выключить реле утечка
#define RELE_U       RB3 = 1, RB2 = 0                  //Выключить реле норма, включить реле утечка
#define RELE_E       RB3 = 0, RB2 = 0                  //Выключить оба реле
/////////////////////////////////

unsigned short uSecond;                                //Счетчик милисекунд
unsigned short second;                                 //Счетчик секунд
unsigned short minute;                                 //Счетчик минут
//unsigned char uSecond_emi;                             //Счетчик ложных измерений
char status;                                           //Статус УКМ

struct DD{
    union ExternalAdc{
        uint16_t value;
        uint8_t toByte[2];
    }externalAdc;
    union InnerAdc{
        uint16_t value;
        uint8_t toByte[2];
    }innerAdc;
}DeviceData;
#endif	/* MAIN_H */

