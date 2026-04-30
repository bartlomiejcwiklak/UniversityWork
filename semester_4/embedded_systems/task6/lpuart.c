#include "lpuart.h"
#include "gpio.h"

// Definicja rejestru dla zegarów magistrali APB1
#define RCC_APB1ENR2 (*((volatile uint32_t *)(RCC_BASE + 0x5CU)))

// Definicja adresu bazowego Portu C (brakuje jej w Twoim gpio.h)
#define GPIOC ((GPIO_TypeDef *) 0x48000800U)

int LPUART_init(void) {
    // 1. Włącz zegar dla Portu C (Bit 2 w rejestrze AHB2ENR to GPIOC)
    RCC_AHB2ENR |= (1U << 2);

    // Ustawiamy funkcję alternatywną numer 8 (LPUART1)
    // Oba piny to piny "niskie" (0 i 1), więc konfigurujemy tylko rejestr AFRL
    // Czyścimy bity 0-3 (dla PC0) i bity 4-7 (dla PC1)
    GPIOC->AFRL &= ~((0xFU << 0) | (0xFU << 4));
    // Wpisujemy wartość 8 w bity 0-3 oraz w bity 4-7
    GPIOC->AFRL |=  ((8U << 0) | (8U << 4));



    // 2. Konfiguracja pinów PC0 (RX) i PC1 (TX) na tryb Alternate Function (AF)
    // Czyścimy bity dla PC0 (bity 0 i 1) oraz PC1 (bity 2 i 3) w rejestrze MODER
    GPIOC->MODER &= ~((3U << 0) | (3U << 2));
    // Wpisujemy w te same miejsca "10" (co oznacza tryb AF)
    GPIOC->MODER |=  ((2U << 0) | (2U << 2));


    // 3. Włączenie zegara dla bloku LPUART1 (Bit 0 w APB1ENR2)
    RCC_APB1ENR2 |= (1U << 0);

    // 4. Konfiguracja parametrów UART
    // Upewniamy się, że blok sprzętowy LPUART jest wyłączony przed konfiguracją
    LPUART1->CR1 &= ~(1U << 0); // UE = 0

    // Ustawiamy prędkość na 115200 przy zegarze 4 MHz: (256 * 4 000 000) / 115200 = 8889
    LPUART1->BRR = 8889;

    // Włączamy nadajnik (TE) i odbiornik (RE)
    LPUART1->CR1 |= (1U << 3); // Bit 3 - TE
    LPUART1->CR1 |= (1U << 2); // Bit 2 - RE

    // Ostatecznie aktywujemy LPUART1
    LPUART1->CR1 |= (1U << 0); // Bit 0 - UE

    return 0;
}

int LPUART_SendChar(unsigned char data) {
    while ((LPUART1->ISR & (1U << 7)) == 0) {
        // Czekaj, aż bufor nadawania będzie pusty
    }
    LPUART1->TDR = data;
    return 0;
}

int LPUART_ReceiveChar(unsigned char* data) {
    while ((LPUART1->ISR & (1U << 5)) == 0) {
        // Czekaj, aż przyjdzie nowy znak (flaga RXNE się zapali)
    }
    *data = (unsigned char)(LPUART1->RDR & 0xFF);
    return 0;
}

int LPUART_SendString(unsigned char* data) {
    while (*data != '\0') {
        LPUART_SendChar(*data);
        data++;
    }
    return 0;
}
