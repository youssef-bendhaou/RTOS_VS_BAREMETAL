# MMIO et PMIO

Ce sont les deux façons dont un processeur communique avec ses **périphériques** (GPIO, UART, timers, ADC, etc.).

## MMIO — Memory-Mapped I/O

Les registres des périphériques sont **mappés dans le même espace d'adressage que la RAM**. Pour piloter un périphérique, tu lis/écris simplement à une adresse mémoire précise, avec les instructions normales du processeur (`LDR`/`STR` en ARM, `MOV` en x86, etc.).

```c
#define GPIOA_ODR (*(volatile uint32_t*)0x40020014)
GPIOA_ODR |= (1 << 5); // allume la LED sur la broche 5
```

- Utilisé par la quasi-totalité des microcontrôleurs modernes (ARM Cortex-M, RISC-V, AVR...).
- Un seul espace d'adressage à gérer, un seul jeu d'instructions.
- Le mot-clé `volatile` est essentiel : il empêche le compilateur d'optimiser/supprimer ces accès, car la valeur peut changer indépendamment du flot du programme (ex. un registre de statut modifié par le matériel).

## PMIO — Port-Mapped I/O (I/O mappée en ports)

Les périphériques ont leur **propre espace d'adressage**, séparé de la RAM, accessible via des instructions dédiées (ex. `IN`/`OUT` sur x86).

```asm
OUT 0x60, AL   ; écrit la valeur de AL sur le port 0x60
```

- Historiquement utilisé sur x86.
- Rare sur microcontrôleurs modernes — la MMIO a largement pris le dessus.

## Pourquoi c'est central en bare metal

En bare metal, c'est **toi** (ou la HAL que tu utilises) qui manipules directement ces registres pour configurer et piloter chaque périphérique. Comprendre MMIO/PMIO, c'est comprendre la base absolue de la programmation embarquée, RTOS ou pas — un RTOS ne fait qu'ajouter des couches d'abstraction par-dessus les mêmes accès matériels.

Voir aussi : [`hal.md`](hal.md) pour la couche qui encapsule ces accès.
