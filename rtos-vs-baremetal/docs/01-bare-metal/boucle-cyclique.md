# Boucle cyclique (Cyclic Executive)

## Définition

Un **executive cyclique** (ou "super-loop") est l'architecture la plus simple d'une appli bare metal : une boucle infinie qui appelle successivement chaque fonction/tâche, dans un ordre fixe.

```c
void main(void) {
    system_init();

    while (1) {
        read_sensors();
        update_control_logic();
        update_display();
        check_communication();
    }
}
```

## Caractéristiques

- **Déterministe et facile à suivre** : tu lis le code de haut en bas et tu sais exactement dans quel ordre les choses se passent.
- Pas de vrai parallélisme : si `update_display()` prend du temps, tout le reste attend.
- Le "temps réel" est approximé en gardant chaque fonction courte et rapide, pour que le tour de boucle (la période) reste petit et prévisible.
- Souvent combiné avec des interruptions pour les événements urgents (voir [`interruptions-polling.md`](interruptions-polling.md)), le reste étant traité par polling dans la boucle.

## Limites

- Ne scale pas bien : plus tu ajoutes de fonctions, plus la boucle s'allonge et plus il devient difficile de garantir un timing correct pour chaque tâche.
- Aucune notion de priorité : une tâche urgente doit attendre son tour comme les autres (sauf si elle est gérée en interruption).
- Pas de véritable isolation entre tâches — un bug dans une fonction peut bloquer toute la boucle.

## C'est exactement le problème que le RTOS résout

Un RTOS remplace cette boucle unique par plusieurs **tâches indépendantes**, ordonnancées par un **scheduler** selon leur priorité — voir [`docs/02-rtos/kernel-scheduling.md`](../02-rtos/kernel-scheduling.md).

Exemple de code complet : [`examples/bare-metal/blink_cyclic.c`](../../examples/bare-metal/blink_cyclic.c)
