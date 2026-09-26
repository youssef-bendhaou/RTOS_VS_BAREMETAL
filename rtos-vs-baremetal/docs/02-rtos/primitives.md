# Primitives de synchronisation

Les **primitives** sont les outils fournis par le kernel pour faire communiquer et se synchroniser les tâches entre elles (et avec les interruptions), sans qu'elles aient à se marcher dessus.

## Sémaphore

Un compteur utilisé pour signaler un événement ou limiter l'accès à une ressource.

- **Binaire** : vaut 0 ou 1, souvent utilisé pour signaler "un événement s'est produit" (ex. une ISR "donne" le sémaphore, une tâche le "prend" et se réveille).
- **Comptant (counting)** : peut compter plusieurs occurrences d'un événement (ex. nombre d'octets reçus en attente de traitement).

```c
SemaphoreHandle_t xSem;

void ISR_Bouton(void) {
    xSemaphoreGiveFromISR(xSem, NULL);
}

void TaskTraitement(void *p) {
    for (;;) {
        xSemaphoreTake(xSem, portMAX_DELAY); // bloque jusqu'au signal
        handle_button_press();
    }
}
```

## Mutex (Mutual Exclusion)

Protège une ressource partagée (variable globale, périphérique) pour qu'une seule tâche à la fois puisse y accéder. Contrairement à un sémaphore binaire, un mutex a une notion de **propriétaire** et peut gérer l'inversion de priorité (priority inheritance).

## Queue (file de messages)

Permet d'envoyer des données d'une tâche (ou d'une ISR) à une autre, de façon thread-safe, sans variable globale partagée.

```c
QueueHandle_t xQueue;
xQueueSend(xQueue, &donnee, portMAX_DELAY);
xQueueReceive(xQueue, &donnee, portMAX_DELAY);
```

## Event flags / Event groups

Un ensemble de bits qu'une tâche peut attendre (ex. "attends que le bit WIFI_CONNECTÉ ET le bit CONFIG_CHARGÉE soient les deux à 1"). Voir [`events-timers.md`](events-timers.md).

## Pourquoi c'est important

Ces primitives remplacent les techniques bricolées du bare metal (flags globaux `volatile`, désactivation manuelle des interruptions) par des mécanismes **standardisés, sûrs et bien testés**, gérés directement par le kernel.
