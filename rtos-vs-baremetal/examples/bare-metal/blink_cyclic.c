/*
 * Exemple bare metal : faire clignoter une LED + lire un bouton,
 * avec une boucle cyclique (cyclic executive) et un timer logiciel
 * fait "à la main" (comptage de ticks).
 *
 * Illustre : HAL (fonctions GPIO_*), MMIO (implicite dans la HAL),
 * boucle cyclique, polling.
 *
 * Pseudo-code portable, à adapter au microcontrôleur ciblé.
 */

#include <stdint.h>
#include <stdbool.h>

#define LED_PIN     5
#define BUTTON_PIN  3
#define BLINK_PERIOD_MS 500

volatile uint32_t g_tick_ms = 0; // incrémenté par une interruption de timer (SysTick par ex.)

void SysTick_Handler(void) {
    g_tick_ms++;
}

int main(void) {
    system_clock_init();
    GPIO_ClockEnable(GPIOA);
    GPIO_SetMode(LED_PIN, GPIO_MODE_OUTPUT);
    GPIO_SetMode(BUTTON_PIN, GPIO_MODE_INPUT);
    SysTick_Init(1); // interruption toutes les 1 ms

    uint32_t last_blink = 0;

    while (1) {
        /* --- Tâche 1 : clignotement périodique --- */
        if (g_tick_ms - last_blink >= BLINK_PERIOD_MS) {
            GPIO_Toggle(LED_PIN);
            last_blink = g_tick_ms;
        }

        /* --- Tâche 2 : lecture du bouton par polling --- */
        if (GPIO_Read(BUTTON_PIN) == GPIO_LOW) {
            handle_button_press();
        }

        /* --- Tâche 3 : autre traitement applicatif --- */
        update_application_logic();
    }
}
