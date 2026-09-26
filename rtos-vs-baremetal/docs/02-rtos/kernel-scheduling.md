# Kernel & Scheduling

## Le kernel

Le **kernel** (noyau) est le cœur du RTOS. C'est le programme qui :

- gère la liste des tâches et leur état (prête, en cours, bloquée, suspendue) ;
- effectue les **changements de contexte** (context switch) : sauvegarder l'état d'une tâche (registres, pile) et restaurer celui de la suivante ;
- fournit les services de synchronisation (mutex, sémaphores, queues...) et de temps (délais, timers) ;
- réagit aux interruptions matérielles pour, si besoin, réveiller une tâche.

## Une tâche (task / thread)

Une tâche est une fonction qui tourne en boucle, avec sa propre pile mémoire, comme si elle était seule sur le CPU :

```c
void TaskLED(void *pvParameters) {
    for (;;) {
        GPIO_Toggle(LED_PIN);
        vTaskDelay(pdMS_TO_TICKS(500)); // rend la main au scheduler
    }
}
```

## Le scheduler

Le **scheduler** décide, à chaque instant, quelle tâche prête s'exécute sur le CPU. Deux grandes stratégies :

- **Préemptif (le plus courant)** : une tâche de priorité plus haute peut interrompre ("préempter") une tâche de priorité plus basse à tout moment, typiquement sur un tick timer périodique. C'est ce qu'utilisent FreeRTOS et Zephyr par défaut.
- **Coopératif** : une tâche garde la main jusqu'à ce qu'elle la rende volontairement (ex. en appelant une fonction de délai ou d'attente). Plus simple, mais une tâche mal écrite peut bloquer tout le système.

## Pourquoi c'est plus puissant qu'une boucle cyclique

Contrairement à la [boucle cyclique](../01-bare-metal/boucle-cyclique.md) où l'ordre est figé dans le code, le scheduler **réagit dynamiquement** : une tâche urgente (haute priorité) passe devant une tâche moins urgente, même si celle-ci est "en plein milieu" de son travail — ce qui donne un comportement temps réel bien plus fin.

## Le prix à payer

- Chaque tâche consomme de la RAM pour sa propre pile.
- Le changement de contexte a un coût CPU (petit, mais non nul).
- Il faut concevoir soigneusement les priorités et la synchronisation entre tâches pour éviter les problèmes classiques : inversion de priorité, interblocage (deadlock), famine (starvation).
