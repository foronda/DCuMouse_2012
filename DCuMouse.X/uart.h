#ifndef UART_H
#define UART_H

#include "common.h"
#include <uart.h>

#define BAUDRATE 9600
#define BRGVAL ((FCY/BAUDRATE)/16)-1

void InitUART();
void TestUART();

#endif

