#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define FULL 10000

/* Definiciones de tipos */
typedef unsigned int data;
typedef enum { FALSO, VERDADERO } boolean;

struct elem {
    data d;
    struct elem *next;
};

typedef struct elem elem;

struct queue {
    int cnt;
    elem *head;
    elem *tail;
};

typedef struct queue queue;

/* --- Operaciones Básicas --- */

/**
 * Inicializa la cola circular estableciendo el conteo en 0
 * y los punteros en NULL.
 */
void initialize(queue *q) {
    q->cnt = EMPTY;
    q->head = NULL;
    q->tail = NULL;
}

/**
 * Verifica si la cola no tiene elementos.
 */
boolean empty(const queue *q) {
    return (boolean)(q->cnt == EMPTY);
}

/**
 * Verifica si la cola ha alcanzado el límite definido.
 */
boolean full(const queue *q) {
    return (boolean)(q->cnt >= FULL);
}

/**
 * Agrega un elemento al final de la cola. 
 * En una cola circular, el nuevo tail siempre apunta al head.
 */
void enqueue(data d, queue *q) {
    if (full(q)) return;

    elem *p = malloc(sizeof(elem));
    assert(p != NULL);
    p->d = d;

    if (empty(q)) {
        q->head = p;
        q->tail = p;
        p->next = q->head; // Apunta a sí mismo para cerrar el círculo
    } else {
        p->next = q->head;   // El nuevo elemento apunta al inicio
        q->tail->next = p;   // El anterior tail ahora apunta al nuevo elemento
        q->tail = p;         // Actualizamos el tail
    }
    q->cnt++;
}

/**
 * Elimina el elemento al inicio (head) y lo devuelve.
 * Reajusta el puntero del tail para mantener la circularidad.
 */
data dequeue(queue *q) {
    assert(!empty(q));

    data d;
    elem *p;

    p = q->head;
    d = p->d;

    if (q->cnt == 1) {
        q->head = NULL;
        q->tail = NULL;
    } else {
        q->head = q->head->next; // Movemos la cabeza al siguiente
        q->tail->next = q->head; // El tail se conecta con la nueva cabeza
    }

    free(p);
    q->cnt--;
    return d;
}

/**
 * Devuelve el dato almacenado en la cabeza sin eliminarlo.
 */
data head(const queue *q) {
    assert(!empty(q));
    return q->head->d;
}

/**
 * Devuelve el dato almacenado en la cola (tail) sin eliminarlo.
 */
data tail(const queue *q) {
    assert(!empty(q));
    return q->tail->d;
}

#endif
