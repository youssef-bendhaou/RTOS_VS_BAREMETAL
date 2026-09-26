# Zephyr & FreeRTOS

Ce sont les deux RTOS open-source les plus utilisés dans l'embarqué aujourd'hui. Ils implémentent tous les concepts vus dans les fichiers précédents (kernel, scheduler, primitives, events, timers, blocking), mais avec des philosophies différentes.

## FreeRTOS

- Créé en 2003, maintenu aujourd'hui par **Amazon Web Services**.
- **Un vrai micro-kernel** : très petit (quelques Ko de flash / Ko de RAM pour le noyau seul), scheduler + primitives de base (tâches, queues, sémaphores, mutex, software timers).
- Ne fournit **pas** de pile réseau, drivers matériels génériques ou build system complet par défaut : tu ajoutes toi-même (ou via les SDK des fabricants comme STM32Cube, ESP-IDF, NXP MCUXpresso) les drivers, la HAL, le TCP/IP, etc.
- Idéal quand tu veux un scheduler RTOS minimal, sans imposer une architecture logicielle complète.
- Licence MIT.

## Zephyr

- Projet open-source hébergé par la **Linux Foundation**.
- Un OS complet, pas seulement un scheduler : il embarque son propre système de build (CMake + Kconfig, repris du monde Linux), une description matérielle via **devicetree**, un modèle de driver unifié, et de nombreux stacks intégrés (Bluetooth LE, réseau IP, USB, gestion d'énergie, MMU/MPU...).
- Le noyau lui-même reste modulaire et peut être compilé "petit" pour des cibles très contraintes, mais l'écosystème autour est bien plus riche que FreeRTOS.
- Bon choix quand le projet a besoin de connectivité (Bluetooth, Thread, Wi-Fi) et d'un build system standardisé dès le départ.
- Licence Apache 2.0.

## Points communs (ce que les deux t'apportent par rapport au bare metal)

- Scheduler préemptif par priorité.
- Sémaphores, mutex, queues, event flags, software timers.
- Support multi-architecture (ARM Cortex-M, RISC-V, Xtensa...).
- Communauté active, nombreux exemples et drivers déjà écrits.

## Comment choisir entre les deux (résumé)

| Besoin | Choix probable |
|---|---|
| Scheduler minimal, tu gères le reste toi-même | FreeRTOS |
| Projet IoT avec Bluetooth/réseau, besoin d'un écosystème complet | Zephyr |
| Très petite cible (quelques Ko de RAM) | FreeRTOS |
| Standardisation multi-projets, build system unifié | Zephyr |

> Note : ces infos évoluent — vérifie toujours la documentation officielle ([freertos.org](https://www.freertos.org) et [zephyrproject.org](https://zephyrproject.org)) pour les détails à jour (versions, licences, matériel supporté).
