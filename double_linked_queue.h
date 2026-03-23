#ifndef DOUBLE_LINKED_QUEUE_H
#define DOUBLE_LINKED_QUEUE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define FULL 10000

/* Definiciones de tipos */
typedef unsigned int data;
typedef enum { FALSO, VERDADERO } boolean;

/* Nodo con doble enlace */
struct elem {
    data d;
    struct elem *next; // Apunta al siguiente (hacia el tail)
    struct elem *prev; // Apunta al anterior (hacia el head)
};

typedef struct elem elem;

struct queue {
    int cnt;
    elem *head;
    elem *tail;
};

typedef struct queue queue;

/* --- Operaciones Básicas --- */

void initialize(queue *q) {
    q->cnt = EMPTY;
    q->head = NULL;
    q->tail = NULL;
}

boolean empty(const queue *q) {
    return (boolean)(q->cnt == EMPTY);
}

boolean full(const queue *q) {
    return (boolean)(q->cnt >= FULL);
}

/**
 * Encolar: Agrega al final (tail).
 * El nuevo nodo apunta hacia atrás al viejo tail.
 */
void enqueue(data d, queue *q) {
    if (full(q)) return;

    elem *p = malloc(sizeof(elem));
    assert(p != NULL);

    p->d = d;
    p->next = NULL; // Será el último, no tiene siguiente
    p->prev = q->tail; // Su anterior es el que antes era el último

    if (empty(q)) {
        q->head = p;
    } else {
        q->tail->next = p; // El viejo tail ahora apunta hacia adelante al nuevo
    }
    
    q->tail = p; // El nuevo nodo es ahora el tail
    q->cnt++;
}

/**
 * Desencolar: Quita del frente (head).
 * El nuevo head debe perder su enlace 'prev' para quedar limpio.
 */
data dequeue(queue *q) {
    assert(!empty(q));

    elem *p = q->head;
    data d = p->d;

    q->head = q->head->next; // La cabeza avanza

    if (q->head == NULL) {
        // Si la cola quedó vacía
        q->tail = NULL;
    } else {
        // El nuevo head ya no tiene a nadie antes de él
        q->head->prev = NULL;
    }

    free(p);
    q->cnt--;
    return d;
}

data head(const queue *q) {
    assert(!empty(q));
    return q->head->d;
}

data tail(const queue *q) {
    assert(!empty(q));
    return q->tail->d;
}

#endif
