# RTOS — Real-Time Operating System

Un **RTOS** est un système d'exploitation léger, conçu pour l'embarqué, qui gère plusieurs "tâches" (des fonctions qui semblent s'exécuter en parallèle) avec des garanties de timing prévisibles.

## Caractéristiques principales

- **Nice but complex** : puissant et bien plus scalable qu'une boucle cyclique, mais demande de comprendre de nouveaux concepts (kernel, scheduler, primitives de synchro...).
- Le code applicatif est découpé en **tâches indépendantes**, chacune avec sa propre pile et sa propre logique.
- Un **scheduler** décide, à chaque instant, quelle tâche a le droit de s'exécuter.
- Les interruptions et le polling **assistent** l'application (ils notifient le kernel) plutôt que de la piloter directement.

## Les briques essentielles

| Sujet | Fichier |
|---|---|
| Kernel & Scheduling | [`kernel-scheduling.md`](kernel-scheduling.md) |
| Primitives (mutex, sémaphores, queues...) | [`primitives.md`](primitives.md) |
| Events & Software Timers | [`events-timers.md`](events-timers.md) |
| Blocking (attente bloquante) | [`blocking.md`](blocking.md) |
| Zephyr & FreeRTOS | [`zephyr-freertos.md`](zephyr-freertos.md) |

## En une phrase

> Dans un RTOS, **c'est le kernel qui est le scheduler** : tu déclares des tâches et des besoins de synchronisation, et le kernel se charge de l'ordonnancement — plus flexible, mais tu délègues le contrôle fin du timing.

Voir un exemple minimal : [`examples/rtos/blink_freertos_task.c`](../../examples/rtos/blink_freertos_task.c)
