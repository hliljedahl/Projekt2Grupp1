/* 
 * File:   temp_1.c
 * Author: arvidpersson
 *
 * Created on April 8, 2018, 10:37 PM
 */

void Lcd4_Shift_Left();
void Lcd4_Shift_Right();
void Lcd4_Write_String(char *a);
void Lcd4_Write_Char(char a);
void Lcd4_Init();
void Lcd4_Set_Cursor(char a, char b);
void Lcd4_Clear();
void Lcd4_Cmd(char a);
void Lcd4_Port(char a);
void __delay_s(int d);

PWM1_Init(long fre);
PWM2_Init(long fre);
PWM1_Duty(unsigned int duty);
PWM2_Duty(unsigned int duty);
PWM_Max_Duty();
PWM1_Start();
PWM2_Start();

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
#include <pic16f883.h>
#include "config.h"

#define MAX 10
#define TMR2PRESCALE 4
#define _XTAL_FREQ 8000000

long freq;

void main(){  
    
    unsigned int i = 0;

    bool RB7_flag = true; 
    bool RB6_flag = true; 

    PWM1_Init(5000);
    PWM2_Init(5000);

    ANSELbits.ANS1 = 1; //AR1 -> analog
    
    TRISAbits.TRISA1 = 1;   //AR1 -> ingånh(pot)
    TRISCbits.TRISC1 = 0;   //RC1 -> PMW(led)
    TRISCbits.TRISC2 = 0;   //RC2 -> PWM(led))
    //TRISCbits.TRISC6 = 1;   //RX
    //TRISCbits.TRISC7 = 0;   //TX
    TXSTAbits.TXEN = 1; //startaR EUSART
    TXSTAbits.SYNC = 0; //asynchronous
    RCSTAbits.SPEN = 1; //auto konfig av TX pin
    BAUDCTLbits.BRG16 = 1;
    TXSTAbits.BRGH = 1;
    
    TXREG = 0;
    
    while(true){
        TXREG = 'A';
        while(!TRMT);
    }
    
    /*PORTCbits.RC1 = 0;  //RC1 -> 0(av)
    PORTCbits.RC2 = 0;  //RC2 -> 0(av))
    
    ADCON0 = 0b11000101;    //int osc(max 500kHz), AN1(ADC), ADON
    ADCON1 = 0b10000000;    //2 MSB -> ADRESLH, 8 LSB -> ADRESL  

    PWM1_Duty(0);
    PWM2_Duty(0);
    PWM1_Start();
    PWM2_Start();
    */
    
    
    
    /*while(true){
        __delay_ms(1);
        ADCON0bits.GO_DONE = 1;
        while(ADCON0bits.GO_nDONE){}
        if(ADRESL > 4){
            PWM1_Duty(ADRESL);
        }
     */
}









//#################LCD###########
/*
void __delay_s(int d){
    for(int i=0;i<d;i++){
        __delay_ms(1000);
    }
}

void Lcd4_Port(char a){
	if(a & 1){
        D4 = 1;
    }else{ 
		D4 = 0;
	}
	if(a & 2){
		D5 = 1;
	}else{
		D5 = 0;
	}
	if(a & 4){
		D6 = 1;
	}else{
		D6 = 0;
	}
	if(a & 8){
		D7 = 1;
	}else{
		D7 = 0;
    }
}

void Lcd4_Cmd(char a){ 
	RS = 0; 
	Lcd4_Port(a);
    EN = 1;     
    __delay_ms(4);
    EN = 0;    
}

void Lcd4_Clear(){
	Lcd4_Cmd(0);
	Lcd4_Cmd(1);
}

void Lcd4_Set_Cursor(char a, char b){
	char temp,z,y;
	if(a == 1){
	  temp = 0x80 + b;
		z = temp>>4;
		y = (0x80+b) & 0x0F;
		Lcd4_Cmd(z);
		Lcd4_Cmd(y);
	}
	else if(a == 2){
		temp = 0xC0 + b;
		z = temp>>4;
		y = (0xC0+b) & 0x0F;
		Lcd4_Cmd(z);
		Lcd4_Cmd(y);
	}
}

void Lcd4_Init(){
    Lcd4_Port(0x00);
    __delay_ms(20);
    Lcd4_Cmd(0x03);
    __delay_ms(5);
    Lcd4_Cmd(0x03);
    __delay_ms(11);
    Lcd4_Cmd(0x03);

    Lcd4_Cmd(0x02);    
    Lcd4_Cmd(0x02);
    Lcd4_Cmd(0x08); 	
    Lcd4_Cmd(0x00); 
    Lcd4_Cmd(0x0C);     
    Lcd4_Cmd(0x00);    
    Lcd4_Cmd(0x06);   
}

void Lcd4_Write_Char(char a){
    char temp,y;
    temp = a&0x0F; 
    y = a&0xF0;	
	RS = 1;
    Lcd4_Port(y>>4);    //Data transfer
    EN = 1;
    __delay_ms(5);
    EN = 0;
    Lcd4_Port(temp);
    EN = 1;
    __delay_ms(5);
    EN = 0;
}

void Lcd4_Write_String(char *a){ 
	for(int i=0;a[i]!='\0';i++){
        Lcd4_Write_Char(a[i]);
    }
}

void Lcd4_Shift_Right(){
	Lcd4_Cmd(0x01);
	Lcd4_Cmd(0x0C);
}

void Lcd4_Shift_Left(){
	Lcd4_Cmd(0x01);
	Lcd4_Cmd(0x08);
}
*/


//#############PWM#############


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


 //int adc on RA1
   /*ADCON0 = 0b11000110; 
   TRISAbits.TRISA1 = 1;
   ANSELbits.ANS1 = 1;
   ADCON1 = 0b10000000;
   while(true){
        for(int i=0;i<1000;i++){}
        ADCON0bits.GO_DONE = 1;
        while(ADCON0bits.GO_nDONE){}
        
        PORTAbits.RA2 = ADRESL; 
   }
   */


  /*TRISAbits.TRISA0 = 1; // AN0 input    
    TRISAbits.TRISA1 = 1;
    ADCON1 = 0b10000000; // right justify, Vdd/Vss Vre
    ANSELbits.ANS0 = 1; // set RA0 to analog 
    ADCON0 = 0b11000001; // ADC frec clock 
    
    while(true){
        for(int i=0;i<1000;i++){}
        ADCON0bits.GO = 1;
        for(int i=0;i<1000;i++){}   
        while(ADCON0bits.GO_nDONE){}
        
    }*/
    