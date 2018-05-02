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
#include <math.h>
#include <string.h>

#define _XTAL_FREQ 8000000

Init_uart();    //baud 4800
Init_ADC(); 
__delays_s(int nr_sec);
send_temp(double raw_temp);
test_send_temp();

int avr(); 
int conv_dec_hel(float float_temp);
double Thermister(int RawADC); 
double sendVal = 0;
double raw_temp;

void main(){
    Init_uart();
    Init_ADC();
    while(true){
        //sendVal = Thermister(avr()*(1023/254));
        //send_temp(sendVal);
        test_send_temp();
        __delays_s(1);
    }
}

__delays_s(int nr_sec){
    for(int i=0;i<nr_sec;i++){
        __delay_ms(900);
    }
}

test_send_temp(){
   TXREG = 88;
   while(!PIR1bits.TXIF){}
}


send_temp(double temp_val){ 
    //float test1 = 12.5;
    while(!PIR1bits.TXIF){}
    __delay_ms(1);
    TXREG = (int)temp_val; //skickar heltal  
    while(!PIR1bits.TXIF){}
    __delay_ms(1);
    TXREG = conv_dec_hel(temp_val); // konverterar dec till heltal 
}

int conv_dec_hel(float float_temp){
    int send_dec = 0;
    send_dec = (float_temp-(int)float_temp)*100;
    return send_dec; 
}

double Thermister(int RawADC) {  //Function to perform the fancy math of the Steinhart-Hart equation
 double Temp;
 Temp = log(((10240000/RawADC) - 10000));
 Temp = 1 / (0.001129148 +(0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp);
 Temp = Temp - 273.15;              // Convert Kelvin to Celsius
 return Temp;
}

int avr(){
    int val[10] = {0}, sum = 0, msg = 0;
    int nr = 2;
    for(int i=0;i<nr;i++){
        __delay_ms(1); 
        ADCON0bits.GO_DONE = 1;
        while(ADCON0bits.GO_DONE != 0){}
        ADCON0bits.GO_DONE = 0;
        val[i] = ADRESH; 
    }
    for(int i=0;i<nr;i++){
        sum+=val[i];
    }
    return (sum/nr); 
}

Init_ADC(){
    ANSELbits.ANS1 = 1; //AR1 -> analog 
    TRISAbits.TRISA1 = 1;   //AR1 -> ingång(pot)   
    ADCON0 = 0b11000101;    //int osc(max 500kHz), AN1(ADC), ADON
    ADCON1 = 0b00000000;    //2 MSB -> ADRESLH, 8 LSB -> ADRESL  
}

Init_uart(){
    TXSTAbits.TXEN = 1; 
    TXSTAbits.SYNC = 0;
    RCSTAbits.SPEN = 1; 
    TXSTAbits.BRGH = 0;
    BAUDCTLbits.BRG16 = 1;  
    SPBRG = 51;
}