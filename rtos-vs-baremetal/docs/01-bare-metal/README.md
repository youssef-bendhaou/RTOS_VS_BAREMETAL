# Bare Metal

Le **bare metal** désigne le fait de programmer un microcontrôleur sans système d'exploitation : ton code s'exécute directement sur le matériel ("sur le métal nu"), sans couche d'abstraction de type OS/kernel entre ton application et le processeur.

## Caractéristiques principales

- **Simple mais basique** : pas de scheduler, pas de tâches, pas de gestion mémoire dynamique complexe — tu écris un programme unique, linéaire.
- Tout le contrôle du timing et de l'ordre d'exécution est **entre tes mains**.
- Empreinte mémoire minimale, temps de démarrage quasi instantané, comportement très déterministe.
- Devient vite difficile à maintenir quand le nombre de tâches/fonctionnalités augmente (tout est entremêlé dans une seule boucle).

## Les briques essentielles

| Sujet | Fichier |
|---|---|
| HAL (Hardware Abstraction Layer) | [`hal.md`](hal.md) |
| MMIO / PMIO (accès aux registres) | [`mmio-pmio.md`](mmio-pmio.md) |
| Boucle cyclique (cyclic executive) | [`boucle-cyclique.md`](boucle-cyclique.md) |
| Interruptions vs Polling | [`interruptions-polling.md`](interruptions-polling.md) |

## En une phrase

> En bare metal, **c'est toi le scheduler** : ton `while(1)` et tes interruptions décident de tout, ce qui rend le code facile à suivre mais peu scalable.

Voir un exemple minimal : [`examples/bare-metal/blink_cyclic.c`](../../examples/bare-metal/blink_cyclic.c)
