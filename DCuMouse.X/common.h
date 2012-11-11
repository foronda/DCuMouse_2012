#ifndef __C30_VERSION__
    #define __C30_VERSION__
#endif

#ifndef COMMON_H
#define COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

#define FCY 40000000UL          // 40 MIPS
#define Fosc 80000000           // Fosc = 2*FCY (80 MHz)
#define MIPS 40                 // MIPS = Fcy/1000000
#define TCY  1/FCY              // TCY = 1/Fcy
                                // TCY = 4*Tosc

#include <p33FJ128MC804.h>
#include <libpic30.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


#ifdef	__cplusplus
}
#endif

#endif  /*COMMON.H*/


