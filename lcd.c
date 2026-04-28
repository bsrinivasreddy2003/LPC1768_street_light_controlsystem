#include<lpc17xx.h>
#include "lcd.h"
void delay(unsigned int i);
void lcd_config(){
LPC_GPIO0->FIODIR = RS | EN | DATA;
lcd_cmd(0x38);
lcd_cmd(0x0E);
//lcd_cmd(0x80);
//lcd_cmd(0x01);
lcd_cmd(0xC0);
lcd_cmd(0x01);
}
void lcd_cmd(unsigned char c)
{
LPC_GPIO0->FIOCLR = DATA;
LPC_GPIO0->FIOSET = (c<<15);
LPC_GPIO0->FIOCLR = RS;
LPC_GPIO0->FIOSET = EN;
delay(5);
LPC_GPIO0->FIOCLR = EN;
delay(5);
}
void lcd_data(unsigned char d)
{
LPC_GPIO0->FIOCLR = DATA;
LPC_GPIO0->FIOSET = (d<<15);
LPC_GPIO0->FIOSET = RS;
LPC_GPIO0->FIOSET = EN;
delay(5);
LPC_GPIO0->FIOCLR = EN;
delay(5);}
void lcd_str(unsigned char arr[30])
{
int i;
for(i=0;arr[i]!='\0';i++){
lcd_data(arr[i]);
}}
void lcd_num(unsigned int num)
{
if(num){
lcd_num(num/10);
lcd_data(num%10+0x30);}}
void delay(unsigned int i)
{
int j,k;
for(j=0;j<i;j++)
for(k=0;k<3000;k++);
}