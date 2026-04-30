#include "gpio.h"
#include "lpuart.h"

int main(void) {
    // Zastępujemy poprzednie wywołania board_init(), funkcją konfiguracyjną UART
    LPUART_init();

    // Wymóg 1. Wyślij alfabet przy użyciu pojedynczych wywołań SendChar
    unsigned char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\r\n";
    for (int i = 0; alphabet[i] != '\0'; i++) {
        LPUART_SendChar(alphabet[i]);
    }

    // Wymóg 2. Wyślij łańcuch znaków za pomocą pętli SendString
    // Pamiętaj o podmianie wpisu <Twoje imie> na coś realnego :)
    unsigned char welcome_msg[] = "Welcome, Bartek\r\n";
    LPUART_SendString(welcome_msg);

    // Wymóg 3. Nieskończona pętla (Echo + konwersja małe/duże litery)
    unsigned char current_char;

    while (1) {
        // Oczekujemy w nieskończoność na nowy znak wysłany z PC w minicom
        LPUART_ReceiveChar(&current_char);

        // Operujemy na kodach ASCII
        // Litery 'a' do 'z' to kody 97 - 122. Różnica między małą a dużą (odpowiednikiem) w ASCII to zawsze wartość 32.
        if (current_char >= 'a' && current_char <= 'z') {
            current_char -= 32; // Zrób z małej literę WIELKĄ
        }
        else if (current_char >= 'A' && current_char <= 'Z') {
            current_char += 32; // Zrób z WIELKIEJ literę małą
        }
        // Znaki interpunkcyjne oraz cyfry zostają pominięte w blokach 'if', więc nic z nimi nie robimy (zgodnie z poleceniem).

        // Po transformacji odsyłamy dany znak prosto do komputera
        LPUART_SendChar(current_char);
    }

    return 0;
}
