#include<lpc17xx.h>
#include "lcd.h"
#include "lcd.c"
#define led1 (1<<20)
#define led2 (1<<12)
#define ir1 (1<<14)
#define ir2 (1<<17)
void light1();
void light2();
//void delay(unsigned int i);
unsigned int adc1_value;
int main(){
lcd_config();
LPC_SC->PCONP |=(1<<12); //sc-system control,enable power ADC
LPC_SC->PCLKSEL0|= (1<<25)|(1<<24);//enable clk for adc
LPC_PINCON->PINSEL1 |= (1<<16); //config P0.24 of AIN2 AD0.1
LPC_ADC->ADCR=(1<<1)|(4<<8)|(1<<16)|(1<<21);
LPC_GPIO1->FIODIR &=~ir1;
LPC_GPIO1->FIODIR &=~ir2;
LPC_GPIO1->FIODIR &=(0xFF<<19);
LPC_GPIO1->FIOCLR =(0xFF<<19);
lcd_cmd(0x01);
lcd_cmd(0x80);
lcd_str("AUTOMATIC STREET");
lcd_cmd(0xc0);
lcd_str("LIGHT CONTROL");
delay(1000);
while(1){
while(!(LPC_ADC->ADGDR&(1<<31)));  //CHECK done bit set or not using polling statement
adc1_value=(LPC_ADC->ADDR1&(0xFFF<<4)); //read the digital value to any variable
adc1_value=adc1_value>>4;  // right shift by 4 to get lsb
lcd_cmd(0x01);
lcd_cmd(0x80);
lcd_str("Light intensity:");
lcd_cmd(0xc0);
lcd_num(adc1_value);
delay(1000);
light1();
light2();	    }}
void light1(){
if((LPC_GPIO1->FIOPIN&(ir1)))  {
if(adc1_value>3000){
LPC_GPIO1->FIOSET=led1;
delay(1000);
LPC_GPIO1->FIOCLR=led1;
delay(1000);   }}}
void light2(){
if((LPC_GPIO1->FIOPIN&(ir2)))  {
if(adc1_value>3000){
LPC_GPIO1->FIOCLR=led2;
delay(1000);
LPC_GPIO1->FIOSET=led2;
delay(1000);   }}}


