/* 
 * File:   uart.h
 * Author: user145
 *
 * Created on 17 июля 2018 г., 16:40
 */

#ifndef UART_H
#define	UART_H
#include <htc.h>
#include "util.h"
#include "main.h"

#define RX PORTBbits.RB6
#define TX PORTBbits.RB7

#define SET_TX TX = TRUE

#define CLEAR_TX TX = FALSE

#define TIMEOUT 79  //для скорости 9600 бод

void pushByte(byte b);

#endif	/* UART_H */

