#include "stm32f30x.h"                  // Device header
#include "serial_stdio.h"
#include "retarget_stm32f3.h"
#include "delay.h"
#include <string.h>
#include "dma_usart2.h"
/*Led PB13, Button PC13*/

void led_init(void);

Serial_t USART1_Serial={USART1_getChar,USART1_sendChar};
Serial_t USART2_Serial={USART2_getChar,USART2_sendChar};

char mybf[80];/*Input buffer*/
char wordBuffer[80];

int main(){
	char message[] = "Hello\n";
	char message2[] = "World\n";
	led_init();
	USART2_init(9600);
	dma_usart2_init();
	usart2_enable_dma();
	dma_usart2_start("\nSystem ready!\n");
	while(1){
		dma_usart2_start(message);
		dma_usart2_start(message2);
		delay_ms(1000);
	}
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
