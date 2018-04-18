/* 
 * File:   main_12f675.c
 * Author: arvidpersson
 *
 * Created on April 17, 2018, 7:46 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <stdbool.h>
#include <pic12f675.h> 
#include <math.h>
#include <xc.h>
#include <string.h>

#define _XTAL_FREQ 4000000

void init_fosc();

void main(){
    init_fosc();
    TRISIO = 0;
    GPIO5 = 0;
    
    while(true){
       GPIO5 = 1;
       __delay_ms(1000);
       GPIO5 = 0;
       __delay_ms(1000);
    }    
}

void init_fosc(){
    OSCCAL = 0b11111100;
}
