#ifndef _DMA_USART2_H
#define _DMA_USART2_H

#ifdef __cplusplus
extern "C" {
#endif

void dma_usart2_init(void);

void usart2_enable_dma(void);

void dma_usart2_irq_enable(void);

void dma_usart2_irq_disable(void);

void dma_usart2_start(const char* pString);

#ifdef __cplusplus
}
#endif


#endif// _DMA_USART2_H
