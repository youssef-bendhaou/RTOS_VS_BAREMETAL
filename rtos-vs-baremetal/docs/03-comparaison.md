# Comparaison détaillée : quand choisir quoi ?

## Tableau récapitulatif du vocabulaire

| Terme | Bare Metal | RTOS |
|---|---|---|
| Structure du programme | Boucle cyclique unique | Plusieurs tâches indépendantes |
| Qui ordonnance ? | Toi, dans l'ordre du code | Le kernel, via le scheduler |
| Accès matériel | HAL, MMIO, PMIO, périphériques | Idem, mais encapsulé dans des drivers RTOS |
| Réaction aux événements | Interruptions/polling **pilotent** l'appli | Interruptions/polling **assistent** l'appli (notifient le kernel) |
| Synchronisation | Flags globaux `volatile`, désactivation d'IRQ | Primitives : sémaphores, mutex, queues, events |
| Attente | Boucle d'attente qui bloque tout | Blocking propre, seule la tâche concernée attend |
| Échéances temporelles | Comptage de ticks manuel | Software timers gérés par le kernel |
| Exemple d'implémentation | Code C nu | Zephyr, FreeRTOS |

## Quand choisir le bare metal

- Projet **petit et simple** (une poignée de fonctions, pas de vrai besoin de parallélisme).
- Ressources **très limitées** (quelques centaines d'octets de RAM, microcontrôleur 8 bits).
- Besoin d'un contrôle du timing **au cycle près** (drivers bas niveau, bootloader, code de démarrage).
- Équipe qui débute en embarqué : comprendre le bare metal d'abord aide énormément à comprendre ensuite ce qu'un RTOS automatise.

## Quand choisir un RTOS

- Plusieurs fonctionnalités **concurrentes** avec des contraintes de timing différentes (ex. lire un capteur toutes les 10 ms, gérer une UI, gérer du réseau, tout en même temps).
- Le projet va **grossir** dans le temps (ajout de fonctionnalités sans tout réécrire).
- Besoin de stacks logiciels tout faits (Bluetooth, TCP/IP, USB) — Zephyr et FreeRTOS ont des écosystèmes riches pour ça.
- Une équipe de plusieurs développeurs qui doivent travailler sur des tâches indépendantes sans se marcher dessus.

## Ce qui ne change PAS entre les deux

Quel que soit ton choix, tu manipuleras toujours :

- une **HAL** pour parler au matériel,
- des registres via **MMIO/PMIO**,
- des **interruptions** pour réagir aux événements matériels.

La vraie différence est **qui orchestre tout ça** : toi directement (bare metal) ou un kernel via un scheduler (RTOS).

## En résumé

> **Bare metal = tu es le chef d'orchestre.**
> **RTOS = tu délègues l'orchestration au kernel, et tu te concentres sur la logique de chaque tâche.**

Aucun des deux n'est "meilleur" dans l'absolu — c'est un compromis entre simplicité/contrôle total et scalabilité/productivité.
