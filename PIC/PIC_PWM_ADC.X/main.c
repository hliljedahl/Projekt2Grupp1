/* 
 * File:   main.c
 * Author: arvidpersson
 *
 * Created on April 11, 2018, 1:31 PM
 */

__delay_s(int d);
Init_PWM(int P1, int P2,int fre1, int fre2);
PWM1_Init(long fre);
PWM2_Init(long fre);
PWM1_Duty(unsigned int duty);
PWM2_Duty(unsigned int duty);
PWM_Max_Duty();
PWM1_Start();
PWM2_Start();
Init_ADC();

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
#include <pic16f883.h>
#include "config.h"

#define TMR2PRESCALE 4
#define _XTAL_FREQ 8000000

long freq;

void main(){  
    
    unsigned int i = 0;
    
    Init_ADC(); //init ADC(pin AR1)
    Init_PWM(1,0,5000,5000); //int PWM RC1, freq -> 5000
    
    while(true){
        __delay_ms(1);
        ADCON0bits.GO_DONE = 1;
        while(ADCON0bits.GO_nDONE){}
        if(ADRESL > 4){
            PWM1_Duty(ADRESL);
        }else{
            PWM1_Duty(0);
        }
    }
}

Init_PWM(int P1, int P2,int fre1, int fre2){
    if(P1){
        TRISCbits.TRISC1 = 0;   //RC1 -> PMW(led)
        PWM1_Init(fre1);
        PWM1_Duty(0);
        PWM1_Start();
    }
    
    if(P2){  
        TRISCbits.TRISC2 = 0;   //RC2 -> PWM(led)) 
        PWM1_Init(fre2);
        PWM2_Duty(0);
        PWM2_Start();
    }
}

Init_ADC(){
    ANSELbits.ANS1 = 1; //AR1 -> analog
    TRISAbits.TRISA1 = 1;   //AR1 -> ing�ng(pot)
    ADCON0 = 0b11000101;    //int osc(max 500kHz), AN1(ADC), ADON
    ADCON1 = 0b10000000;    //2 MSB -> ADRESLH, 8 LSB -> ADRESL  
}

int PWM_Max_Duty(){
  return(_XTAL_FREQ/(freq*TMR2PRESCALE));
}

PWM1_Init(long fre){
  PR2 = (_XTAL_FREQ/(fre*4*TMR2PRESCALE)) - 1;
  freq = fre;
}

PWM2_Init(long fre){
  PR2 = (_XTAL_FREQ/(fre*4*TMR2PRESCALE)) - 1;
  freq = fre;
}

PWM1_Duty(unsigned int duty){
  if(duty<1024){
    duty = ((float)duty/1023)*PWM_Max_Duty();
    CCP1X = duty & 2;
    CCP1Y = duty & 1;
    CCPR1L = duty>>2;
  }
}

PWM2_Duty(unsigned int duty){
  if(duty<1024){
    duty = ((float)duty/1023)*PWM_Max_Duty();
    CCP2X = duty & 2;
    CCP2Y = duty & 1;
    CCPR2L = duty>>2;
  }
}

PWM1_Start(){
  CCP1M3 = 1;
  CCP1M2 = 1;
  #if TMR2PRESCALAR == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
  #elif TMR2PRESCALAR == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
  #elif TMR2PRESCALAR == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
  #endif
  TMR2ON = 1;
  TRISC2 = 0;
}

PWM1_Stop(){
  CCP1M3 = 0;
  CCP1M2 = 0;
}

PWM2_Start(){
  CCP2M3 = 1;
  CCP2M2 = 1;
  #if TMR2PRESCALE == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
  #elif TMR2PRESCALE == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
  #elif TMR2PRESCALE == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
  #endif
    TMR2ON = 1;
    TRISC1 = 0;
}

PWM2_Stop(){
  CCP2M3 = 0;
  CCP2M2 = 0;
}