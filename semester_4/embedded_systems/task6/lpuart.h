#ifndef LPUART_H
#define LPUART_H

#include <stdint.h>

// base address
#define LPUART1_BASE 0x40008000U

// lpuart structure
typedef struct {
    volatile uint32_t CR1;   // 0x00: Control register 1
    volatile uint32_t CR2;   // 0x04: Control register 2
    volatile uint32_t CR3;   // 0x08: Control register 3
    volatile uint32_t BRR;   // 0x0C: Baud rate register
    volatile uint32_t GTPR;  // 0x10: Guard time and prescaler register
    volatile uint32_t RTOR;  // 0x14: Receiver timeout register
    volatile uint32_t RQR;   // 0x18: Request register
    volatile uint32_t ISR;   // 0x1C: Interrupt & status register
    volatile uint32_t ICR;   // 0x20: Interrupt flag clear register
    volatile uint32_t RDR;   // 0x24: Receive data register
    volatile uint32_t TDR;   // 0x28: Transmit data register
} LPUART_TypeDef;

// Mapowanie struktury na konkretny adres w pamięci
#define LPUART1 ((LPUART_TypeDef *) LPUART1_BASE)

// Deklaracje funkcji
int LPUART_init(void);
int LPUART_SendChar(unsigned char data);
int LPUART_ReceiveChar(unsigned char* data);
int LPUART_SendString(unsigned char* data);

#endif // LPUART_H
