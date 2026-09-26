/*
 * Exemple RTOS (FreeRTOS) : équivalent du blink_cyclic.c mais avec
 * des tâches indépendantes, un sémaphore pour le bouton (déclenché
 * par interruption) et un délai bloquant pour le clignotement.
 *
 * Illustre : kernel/scheduling (tâches + priorités), primitives
 * (sémaphore binaire), blocking (vTaskDelay, xSemaphoreTake),
 * interruption qui "assiste" l'appli au lieu de la piloter.
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define LED_PIN     5
#define BUTTON_PIN  3

static SemaphoreHandle_t xButtonSemaphore;

/* --- Tâche 1 : clignotement périodique --- */
void vTaskBlink(void *pvParameters) {
    GPIO_SetMode(LED_PIN, GPIO_MODE_OUTPUT);
    for (;;) {
        GPIO_Toggle(LED_PIN);
        vTaskDelay(pdMS_TO_TICKS(500)); // bloque cette tâche, sans geler les autres
    }
}

/* --- Tâche 2 : traitement du bouton, réveillée par le sémaphore --- */
void vTaskButton(void *pvParameters) {
    GPIO_SetMode(BUTTON_PIN, GPIO_MODE_INPUT);
    for (;;) {
        if (xSemaphoreTake(xButtonSemaphore, portMAX_DELAY) == pdTRUE) {
            handle_button_press();
        }
    }
}

/* --- ISR : ne fait QUE notifier le kernel, ne traite rien elle-même --- */
void EXTI_BUTTON_IRQHandler(void) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    GPIO_ClearInterruptFlag(BUTTON_PIN);
    xSemaphoreGiveFromISR(xButtonSemaphore, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

int main(void) {
    system_clock_init();
    GPIO_ClockEnable(GPIOA);

    xButtonSemaphore = xSemaphoreCreateBinary();

    xTaskCreate(vTaskBlink,  "Blink",  configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vTaskButton, "Button", configMINIMAL_STACK_SIZE, NULL, 2, NULL); // priorité plus haute

    vTaskStartScheduler(); // le kernel prend la main, ordonnance les tâches
    for (;;) { /* ne devrait jamais arriver ici */ }
}
