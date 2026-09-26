# Interruptions vs Polling

Deux façons de détecter et réagir à un événement matériel (bouton pressé, donnée UART reçue, timer expiré...).

## Polling

Le programme **vérifie activement**, en boucle, si un événement s'est produit.

```c
while (1) {
    if (UART_DataAvailable()) {
        process_uart_data();
    }
}
```

- Simple à écrire et à comprendre.
- Gaspille du temps CPU à vérifier "pour rien" quand il n'y a pas d'événement.
- Le temps de réaction dépend de la fréquence à laquelle la boucle repasse sur ce test.

## Interruptions (IRQ)

Le matériel **notifie** le processeur dès qu'un événement se produit, en interrompant le flot normal pour exécuter une fonction dédiée (l'ISR — Interrupt Service Routine).

```c
void USART1_IRQHandler(void) {
    uint8_t data = USART1->DR;
    // traiter la donnée, idéalement vite et court
}
```

- Réaction quasi immédiate, sans gaspiller de cycles CPU en attente.
- Plus complexe : il faut gérer les priorités d'interruption, les sections critiques (protéger les données partagées entre l'ISR et le code principal), et garder les ISR courtes.

## En bare metal : "les interruptions/le polling pilotent l'appli"

En bare metal, il n'y a pas de kernel pour arbitrer : **c'est directement l'interruption (ou le polling dans la boucle) qui déclenche l'action applicative**. L'ISR peut directement modifier l'état de l'application, ou positionner un flag lu ensuite dans la boucle cyclique.

## En RTOS : "elles assistent l'appli"

Dans un RTOS, une interruption ne fait typiquement que **réveiller une tâche** ou **poster un événement/message** au kernel (via une primitive comme un sémaphore ou une queue) — c'est le **scheduler** qui décide ensuite quelle tâche s'exécute et quand. L'interruption assiste donc l'application au lieu de la piloter directement. Voir [`docs/02-rtos/kernel-scheduling.md`](../02-rtos/kernel-scheduling.md) et [`docs/02-rtos/primitives.md`](../02-rtos/primitives.md).
