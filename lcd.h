#include<lpc17xx.h>
#define RS (1<<10)
#define EN (1<<11)
#define DATA (0xFF<<15)
void lcd_config();
void lcd_cmd(unsigned char c);
void lcd_data(unsigned char d);
void lcd_str(unsigned char arr[30]);
void lcd_num(unsigned int num);