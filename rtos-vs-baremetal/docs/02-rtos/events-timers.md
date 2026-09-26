# Events & Software Timers

## Events (événements)

Un **event** (souvent implémenté via un *event group* ou *event flags*) permet à une tâche d'attendre qu'une ou plusieurs conditions soient réunies, sans avoir à faire du polling manuel.

```c
EventGroupHandle_t xEvents;

// Une tâche attend que 2 conditions soient vraies
EventBits_t bits = xEventGroupWaitBits(
    xEvents,
    BIT_WIFI_OK | BIT_CONFIG_OK,
    pdFALSE, pdTRUE,      // ne pas effacer les bits, attendre TOUS les bits
    portMAX_DELAY);
```

C'est une évolution des sémaphores/flags manuels du bare metal, mais gérée et arbitrée par le kernel, avec la possibilité d'attendre des combinaisons de conditions.

## Software Timers (timers logiciels)

Un RTOS fournit des **timers logiciels**, gérés par le kernel (pas besoin d'un timer matériel dédié par fonctionnalité). Un callback est exécuté après un délai, une seule fois ou périodiquement.

```c
TimerHandle_t xTimer = xTimerCreate(
    "Watchdog", pdMS_TO_TICKS(1000), pdTRUE /* auto-reload */,
    NULL, vTimerCallback);
xTimerStart(xTimer, 0);
```

- Contrairement à un timer matériel (limité en nombre), tu peux créer autant de software timers que la RAM le permet.
- Le callback s'exécute dans une tâche dédiée du kernel ("Timer Service Task"), pas dans le contexte d'une interruption — donc il peut appeler des fonctions RTOS classiques sans les restrictions d'une ISR.

## Comparaison avec le bare metal

En bare metal, gérer plusieurs échéances temporelles (ex. "vérifier le capteur toutes les 100 ms" et "envoyer un heartbeat toutes les 5 s") demande souvent de compter manuellement des ticks dans la boucle cyclique. En RTOS, chaque besoin devient un software timer indépendant, plus lisible et plus facile à faire évoluer.
