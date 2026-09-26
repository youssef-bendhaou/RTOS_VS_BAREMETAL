# RTOS vs Bare Metal

Une explication claire et organisée des deux grandes approches pour développer sur microcontrôleur : le **bare metal** (code "nu", sans OS) et le **RTOS** (Real-Time Operating System).

> Le but de cette repo n'est pas de dire "l'un est meilleur que l'autre", mais de comprendre **quand et pourquoi** choisir l'un ou l'autre, et de clarifier tout le vocabulaire qui gravite autour (HAL, MMIO/PMIO, kernel, scheduling, primitives, etc.).

## Vue d'ensemble

| | Bare Metal | RTOS |
|---|---|---|
| Philosophie | Simple mais basique | Puissant mais complexe |
| Structure typique | Boucle cyclique (`while(1)`) | Kernel + tâches (threads) |
| Ordonnancement | Aucun (le code s'exécute dans l'ordre écrit) | Scheduler (préemptif ou coopératif) |
| Synchronisation | Flags globaux, désactivation d'IRQ | Sémaphores, mutex, queues, event flags |
| Temps | Delay/polling manuel | Software timers, délais bloquants gérés par le kernel |
| Accès au matériel | Direct via HAL / MMIO / PMIO | Toujours via HAL / MMIO / PMIO, mais encapsulé par des drivers RTOS |
| Réaction aux événements | Interruptions ou polling pilotent l'appli | Interruptions/polling assistent l'appli (le kernel fait la coordination) |
| Courbe d'apprentissage | Facile à suivre, déterministe "à la main" | Plus abstrait, demande de comprendre le kernel |
| Exemples | Code C nu sur registres, petites appli | Zephyr, FreeRTOS |

## Structure de la repo

- [`docs/01-bare-metal/`](docs/01-bare-metal/README.md) — tout sur l'approche bare metal
- [`docs/02-rtos/`](docs/02-rtos/README.md) — tout sur l'approche RTOS
- [`docs/03-comparaison.md`](docs/03-comparaison.md) — comparaison détaillée, quand choisir quoi
- [`examples/`](examples/) — exemples de code minimalistes (bare metal vs FreeRTOS)

## Par où commencer ?

1. Si tu débutes en embarqué → commence par [bare metal](docs/01-bare-metal/README.md), c'est la base de tout (même un RTOS tourne sur du matériel qu'il faut comprendre).
2. Une fois les bases posées → passe à [RTOS](docs/02-rtos/README.md) pour voir ce qu'un kernel t'apporte en plus.
3. Termine par la [comparaison](docs/03-comparaison.md) pour savoir quoi choisir selon ton projet.

## Licence

MIT — voir [LICENSE](LICENSE).
