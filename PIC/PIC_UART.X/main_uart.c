/* 
 * File:   main_uart.c
 * Author: arvidpersson
 *
 * Created on April 11, 2018, 2:39 PM
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
#include <pic16f883.h>
#include "config.h"

#define _XTAL_FREQ 8000000

Init_uart();    //baud 4800

void main(){
    Init_uart();
    
    while(true){
        TXREG = 65; 
        while(!PIR1bits.TXIF){}
        __delay_ms(500);
    }  
}
Init_uart(){
    TXSTAbits.TXEN = 1; 
    TXSTAbits.SYNC = 0;
    RCSTAbits.SPEN = 1; 
    TXSTAbits.BRGH = 0;
    BAUDCTLbits.BRG16 = 1;
    
    SPBRG = 51;
}