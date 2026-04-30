#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

// peripherals from 2.2.2, p. 77
#define RCC_BASE 0x40021000U
#define PWR_BASE 0x40007000U

// power registers, from 6.4, p. 251
#define RCC_AHB2ENR (*((volatile uint32_t *)(RCC_BASE + 0x4CU)))
#define RCC_APB1ENR1 (*((volatile uint32_t *)(RCC_BASE + 0x58U)))
#define PWR_CR2 (*((volatile uint32_t *)(PWR_BASE  + 0x04U)))

// gpio structure
typedef struct {
    volatile uint16_t CR1;   uint16_t reserved0;
    volatile uint16_t CR2;   uint16_t reserved1;
    volatile uint16_t SMCR;  uint16_t reserved2;
    volatile uint16_t DIER;  uint16_t reserved3;
    volatile uint16_t SR;    uint16_t reserved4;
    volatile uint16_t EGR;   uint16_t reserved5;
    volatile uint16_t CCMR1; uint16_t reserved6;
    volatile uint16_t CCMR2; uint16_t reserved7;
    volatile uint16_t CCER;  uint16_t reserved8;
    volatile uint16_t CNT;   uint16_t reserved9;
    volatile uint16_t PSC;   uint16_t reserved10;
    volatile uint16_t ARR;   uint16_t reserved11;
} TIM_TypeDef;

// timer registers structure
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t CCMR1;
    volatile uint32_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
} TIM_TypeDef;

#define GPIOB ((GPIO_TypeDef *) 0x48000400U)
#define GPIOE ((GPIO_TypeDef *) 0x48001000U)
#define GPIOG ((GPIO_TypeDef *) 0x48001800U)
#define TIM6 ((TIM_TypeDef *) 0x40001000U)

typedef enum {
    GPIO_MODE_INPUT = 0x0U,
    GPIO_MODE_OUTPUT = 0x1U,
    GPIO_MODE_AF = 0x2U,
    GPIO_MODE_ANALOG = 0x3U,
} GPIO_Mode;

typedef enum {
    GPIO_PORT_A = (1U << 0),
    GPIO_PORT_B = (1U << 1),
    GPIO_PORT_C = (1U << 2),
    GPIO_PORT_D = (1U << 3),
    GPIO_PORT_E = (1U << 4),
    GPIO_PORT_F = (1U << 5),
    GPIO_PORT_G = (1U << 6),
} GPIO_PortClock;

void GPIO_ClockEnable(GPIO_PortClock port);

void GPIO_Init(GPIO_TypeDef *port, uint8_t pin, GPIO_Mode mode);

void GPIO_InitRange(GPIO_TypeDef *port, uint8_t start_pin, uint8_t count, GPIO_Mode mode);

void GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, uint8_t value);

void GPIO_WriteMasked(GPIO_TypeDef *port, uint32_t mask, uint32_t value);

uint8_t GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin);

#endif
