# Blocking (attente bloquante)

## Définition

Une tâche RTOS peut se mettre en **attente bloquante** sur une primitive (sémaphore, mutex, queue, event, délai) : elle est retirée de la liste des tâches "prêtes" et **ne consomme aucun cycle CPU** pendant l'attente. Le scheduler donne alors la main à une autre tâche.

```c
void TaskCapteur(void *p) {
    for (;;) {
        xQueueReceive(xQueueCapteur, &valeur, portMAX_DELAY); // bloque ici
        traiter(valeur);
    }
}
```

Quand l'événement attendu arrive (donnée dans la queue, sémaphore donné, délai écoulé...), le kernel remet automatiquement la tâche dans l'état "prête", et le scheduler l'exécutera dès qu'elle a la priorité la plus haute parmi les tâches prêtes.

## Pourquoi c'est puissant

- Le CPU n'est jamais "gaspillé" à checker activement une condition (contrairement au polling pur en bare metal).
- Le code reste **linéaire et lisible** à l'intérieur d'une tâche : tu écris "attends puis fais X" comme une séquence normale, même si en réalité d'autres tâches tournent pendant l'attente.
- Un délai maximum optionnel (`timeout`) permet de ne pas attendre indéfiniment si l'événement n'arrive jamais.

## Le piège à connaître

Bloquer une tâche est normal et voulu. Mais **bloquer dans une ISR est interdit** : une interruption ne doit jamais attendre — elle doit être courte, et déléguer le traitement long à une tâche (via une primitive comme un sémaphore ou une queue, avec les variantes `...FromISR`). C'est exactement le principe "les interruptions assistent l'appli" plutôt que de tout faire elles-mêmes — voir [`../01-bare-metal/interruptions-polling.md`](../01-bare-metal/interruptions-polling.md).

## Comparaison avec le bare metal

En bare metal pur, il n'y a pas de vrai "blocage" sans geler tout le programme (une boucle `while` d'attente bloque tout, puisqu'il n'y a qu'un seul flot d'exécution). Le RTOS rend le blocage **sûr et local à une tâche**, sans affecter les autres.
