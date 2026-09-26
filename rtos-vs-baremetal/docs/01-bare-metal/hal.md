# HAL — Hardware Abstraction Layer

## Définition

La **HAL** est une couche logicielle qui cache les détails du matériel (registres, adresses mémoire, bits de configuration) derrière des fonctions simples à utiliser.

Au lieu d'écrire directement dans un registre :

```c
// Sans HAL — accès direct au registre
*(volatile uint32_t*)0x40021018 |= (1 << 5); // active l'horloge du GPIOA
```

Tu appelles une fonction claire :

```c
// Avec HAL
GPIO_ClockEnable(GPIOA);
```

## Pourquoi une HAL ?

- **Portabilité** : le même code applicatif peut tourner sur plusieurs familles de puces si chacune a sa propre HAL avec la même interface.
- **Lisibilité** : le code métier ne se noie pas dans des manipulations de bits.
- **Moins d'erreurs** : la HAL encapsule la bonne séquence d'initialisation (ordre des registres, masques, etc.).

## Le compromis

- Une HAL ajoute une couche d'indirection → un peu plus de code, parfois un peu moins rapide qu'un accès registre optimisé à la main.
- Sur des projets bare metal très contraints (taille de code, latence critique), certains développeurs préfèrent accéder directement aux registres (MMIO/PMIO — voir [`mmio-pmio.md`](mmio-pmio.md)) plutôt que de passer par la HAL.

## Dans un RTOS

Un RTOS comme Zephyr ou FreeRTOS s'appuie lui aussi sur une HAL (souvent fournie par le fabricant du microcontrôleur, ex. STM32 HAL, nRF SDK) pour ses drivers de périphériques. La différence est que le RTOS ajoute par-dessus une couche de **pilotes et de services** (voir [`docs/02-rtos/`](../02-rtos/README.md)).
