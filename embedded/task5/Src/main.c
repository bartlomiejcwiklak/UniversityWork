#include "gpio.h"

#define COUNT_RATE_MS 1000U

// 4 displays (PB5-PB2)
#define DISPLAY_PORT GPIOB
#define DISPLAY_PIN_BASE 2U
#define DISPLAY_PIN_COUNT 4U

// one 7-segment display (PG0-PG6)
#define SEGMENT_PORT GPIOG
#define SEGMENT_PIN_BASE 0U
#define SEGMENT_PIN_COUNT 7U
#define SEGMENT_MASK 0x7FU

// joystick (PE15)
#define JOYSTICK_PORT GPIOE
#define JOYSTICK_PIN 15U

static const uint8_t digits[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66,
    0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

static void board_init(void) {
    // vddio2 power
    RCC_APB1ENR1 |= (1U << 28);
    PWR_CR2 |= (1U << 9);

    GPIO_ClockEnable(GPIO_PORT_B);
    GPIO_ClockEnable(GPIO_PORT_E);
    GPIO_ClockEnable(GPIO_PORT_G);

    GPIO_InitRange(DISPLAY_PORT, DISPLAY_PIN_BASE, DISPLAY_PIN_COUNT, GPIO_MODE_OUTPUT);
    GPIO_InitRange(SEGMENT_PORT, SEGMENT_PIN_BASE, SEGMENT_PIN_COUNT, GPIO_MODE_OUTPUT);
    GPIO_Init(JOYSTICK_PORT, JOYSTICK_PIN, GPIO_MODE_INPUT);
}

static void TIM6_Init(void) {
    // tim6 power: 4th bit on APB1
    RCC_APB1ENR1 |= (1U << 4);

    // clock is 4MHz, this gives us 1ms
    TIM6->PSC = 4000U - 1U;
    TIM6->ARR = 0xFFFF;

    // FIX: Wymuszenie natychmiastowego przeładowania "shadow registers" (bit UG)
    TIM6->EGR |= (1U << 0);

    TIM6->CR1 |= (1U << 0); // enable the timer (CEN bit)
}

static void TIM6_Delay_ms(uint16_t ms) {
	uint16_t start = TIM6->CNT;
	while ((uint16_t)(TIM6->CNT - start) < ms);
}

static void display_show(uint8_t pos, uint8_t val) {
    GPIO_WriteMasked(DISPLAY_PORT, 0xFU << DISPLAY_PIN_BASE, 0U);
    GPIO_WriteMasked(SEGMENT_PORT, SEGMENT_MASK, 0U);

    GPIO_WriteMasked(SEGMENT_PORT, SEGMENT_MASK, digits[val]);
    GPIO_WritePin(DISPLAY_PORT, 5U - pos, 1U);
}

int main(void) {
    board_init();
    TIM6_Init();

    int counter = 0;
    uint16_t last_tick = TIM6->CNT;

    while (1) {
        display_show(3, (uint8_t)((counter / 1000) % 10)); TIM6_Delay_ms(2);
        display_show(2, (uint8_t)((counter / 100) % 10)); TIM6_Delay_ms(2);
        display_show(1, (uint8_t)((counter / 10) % 10)); TIM6_Delay_ms(2);
        display_show(0, (uint8_t)(counter % 10)); TIM6_Delay_ms(2);

        if ((uint16_t)(TIM6->CNT - last_tick) >= COUNT_RATE_MS) {
			last_tick += COUNT_RATE_MS;
			if (GPIO_ReadPin(JOYSTICK_PORT, JOYSTICK_PIN) == 0) {
				if (--counter < 0) counter = 9999;
			} else {
				if (++counter > 9999) counter = 0;
			}
		}
    }
}
