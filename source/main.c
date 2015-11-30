#include "stm32f30x.h"                  // Device header
#include "serial_stdio.h"
#include "retarget_stm32f3.h"
#include "delay.h"
#include <string.h>
/*Led PB13, Button PC13*/

void led_init(void);

Serial_t USART1_Serial={USART1_getChar,USART1_sendChar};
Serial_t USART2_Serial={USART2_getChar,USART2_sendChar};

char mybf[80];/*Input buffer*/
char wordBuffer[80];

int main(){
	int lineCounter=1;
	led_init();
	USART2_init(9600);
	serial_puts(USART2_Serial,"\nSystem ready\n");
	while(1){
		serial_printf(USART2_Serial,"%d$ ",lineCounter);
		serial_gets(USART2_Serial,mybf,80);
		serial_printf(USART2_Serial,"%s\n",mybf);
		if(sscanf(mybf,"%s",wordBuffer) > 0){
			serial_printf(USART2_Serial,"word: %s\n",wordBuffer);
			serial_printf(USART2_Serial,"characters: %d\n",strlen(wordBuffer));
		}
		lineCounter++;
	}
	return 0;
}


void led_init(void){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	GPIO_InitTypeDef myGPIO;
	GPIO_StructInit(&myGPIO);
	myGPIO.GPIO_Pin=GPIO_Pin_13;
	myGPIO.GPIO_Mode=GPIO_Mode_OUT;
	myGPIO.GPIO_OType=GPIO_OType_PP;
	myGPIO.GPIO_PuPd=GPIO_PuPd_NOPULL;
	myGPIO.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&myGPIO);
	GPIO_WriteBit(GPIOB,GPIO_Pin_13,Bit_RESET);
}
