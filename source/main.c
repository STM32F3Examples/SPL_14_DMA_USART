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

void dma_usart2_init(void){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	DMA_InitTypeDef myDMA;
	DMA_StructInit(&myDMA);
	myDMA.DMA_DIR = DMA_DIR_PeripheralDST;
	myDMA.DMA_M2M = DMA_M2M_Disable;
	myDMA.DMA_Mode = DMA_Mode_Normal;
	myDMA.DMA_Priority = DMA_Priority_Medium;

	myDMA.DMA_PeripheralBaseAddr =(uint32_t) &(USART2->TDR);
	myDMA.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	myDMA.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	myDMA.DMA_MemoryBaseAddr = 0x200000 ;
	myDMA.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	myDMA.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_Init(DMA1_Channel7,&myDMA);// DMA1 Channel 7 =  USART2_Tx
	NVIC_EnableIRQ(DMA1_Channel7_IRQn);
}

void usart2_enable_dma(void){
	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
}

void dma_usart2_irq_enable(){
	DMA_ITConfig(DMA1_Channel7,DMA_IT_TC,ENABLE);
}

void dma_usart2_irq_disable(){
	DMA_ITConfig(DMA1_Channel7,DMA_IT_TC,DISABLE);
}

volatile int dma_usart2_tx_complete = 0;

void DMA1_Channel7_IRQHandler(void){
	DMA_ClearITPendingBit(DMA1_IT_TC7);
	dma_usart2_tx_complete = 1;
}

void dma_usart2_start(const char* pString){
	int strSize = strlen(pString);

	DMA_Cmd(DMA1_Channel7, DISABLE);
	DMA_ClearFlag(DMA1_FLAG_TC7);
	DMA1_Channel7->CMAR =(uint32_t) pString;
	DMA_SetCurrDataCounter(DMA1_Channel7, strSize);

	USART_ClearFlag(USART2, USART_FLAG_TC);
	DMA_ClearFlag(DMA1_FLAG_TC7);
	dma_usart2_tx_complete = 0;

	dma_usart2_irq_enable();
	DMA_Cmd(DMA1_Channel7,ENABLE);

	while(dma_usart2_tx_complete == 0);

	dma_usart2_irq_disable();
}

int main(){
	char message[] = "Hello\n";
	char message2[] = "World\n";
	led_init();
	USART2_init(9600);
	dma_usart2_init();
	usart2_enable_dma();
	while(1){
		dma_usart2_start(message);
		dma_usart2_start(message2);
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
