#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

// ── Peripheral base addresses ─────────────────────────────────────────────────
#define RCC_BASE     0x40021000U
#define PWR_BASE     0x40007000U
#define GPIOB_BASE   0x48000400U
#define GPIOE_BASE   0x48001000U
#define GPIOG_BASE   0x48001800U

// ── Register offsets ──────────────────────────────────────────────────────────
#define MODER_OFFSET 0x00U
#define ODR_OFFSET   0x14U
#define IDR_OFFSET   0x10U

// ── RCC / PWR registers ───────────────────────────────────────────────────────
#define RCC_AHB2ENR  (*((volatile uint32_t *)(RCC_BASE + 0x4CU)))
#define RCC_APB1ENR1 (*((volatile uint32_t *)(RCC_BASE + 0x58U)))
#define PWR_CR2      (*((volatile uint32_t *)(PWR_BASE  + 0x04U)))

// ── GPIO register access macros ───────────────────────────────────────────────
#define GPIO_MODER(base) (*((volatile uint32_t *)((base) + MODER_OFFSET)))
#define GPIO_ODR(base)   (*((volatile uint32_t *)((base) + ODR_OFFSET)))
#define GPIO_IDR(base)   (*((volatile uint32_t *)((base) + IDR_OFFSET)))

// ── Pin mode constants ────────────────────────────────────────────────────────
typedef enum {
    GPIO_MODE_INPUT  = 0x0U,
    GPIO_MODE_OUTPUT = 0x1U,
    GPIO_MODE_AF     = 0x2U,
    GPIO_MODE_ANALOG = 0x3U,
} GPIO_Mode;

// ── Port clock enable bits in RCC_AHB2ENR ────────────────────────────────────
typedef enum {
    GPIO_PORT_A = (1U << 0),
    GPIO_PORT_B = (1U << 1),
    GPIO_PORT_C = (1U << 2),
    GPIO_PORT_D = (1U << 3),
    GPIO_PORT_E = (1U << 4),
    GPIO_PORT_F = (1U << 5),
    GPIO_PORT_G = (1U << 6),
} GPIO_PortClock;

// ── Public API ────────────────────────────────────────────────────────────────

/**
 * Enable the AHB2 clock for a GPIO port.
 * Must be called before any GPIO_Init on that port.
 */
void GPIO_ClockEnable(GPIO_PortClock port);

/**
 * Configure a single pin's mode.
 * @param base  GPIO port base address (e.g. GPIOB_BASE)
 * @param pin   Pin number 0–15
 * @param mode  GPIO_MODE_INPUT / OUTPUT / AF / ANALOG
 */
void GPIO_Init(uint32_t base, uint8_t pin, GPIO_Mode mode);

/**
 * Configure a contiguous range of pins to the same mode.
 * Useful for setting an entire segment bus at once.
 * @param base      GPIO port base address
 * @param start_pin First pin in the range
 * @param count     Number of pins
 * @param mode      Mode to apply to every pin in the range
 */
void GPIO_InitRange(uint32_t base, uint8_t start_pin, uint8_t count, GPIO_Mode mode);

/**
 * Write a single pin HIGH (1) or LOW (0).
 */
void GPIO_WritePin(uint32_t base, uint8_t pin, uint8_t value);

/**
 * Write multiple pins at once using a mask.
 * Only the bits set in `mask` are affected; their values come from `value`.
 * @param base  GPIO port base address
 * @param mask  Bitmask of pins to update
 * @param value New values for the masked pins
 */
void GPIO_WriteMasked(uint32_t base, uint32_t mask, uint32_t value);

/**
 * Read a single pin from IDR.
 * @return 0 or 1
 */
uint8_t GPIO_ReadPin(uint32_t base, uint8_t pin);

/**
 * Read the full IDR of a port.
 */
uint32_t GPIO_ReadPort(uint32_t base);

/**
 * Busy-wait delay.
 */
void delay(uint32_t cycles);

#endif // GPIO_H
