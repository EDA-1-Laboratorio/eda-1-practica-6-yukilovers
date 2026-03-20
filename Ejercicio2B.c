#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 6

char queue[MAX][50];
int front = -1, rear = -1;

// Verifica si la cola está llena
int estaLlena() {
    return (front == (rear + 1) % MAX);
}

// Verifica si la cola está vacía
int estaVacia() {
    return (front == -1);
}

// Enqueue (recibir comanda)
void enqueue(char orden[]) {
    if (estaLlena()) {
        printf("La cola está llena (máximo 6 órdenes).\n");
        return;
    }

    if (estaVacia()) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % MAX;
    }

    strcpy(queue[rear], orden);
    printf("Orden recibida: %s\n", orden);
}

// Dequeue (servir platillo)
void dequeue() {
    if (estaVacia()) {
        printf("No hay órdenes por servir.\n");
        return;
    }

    printf("Sirviendo: %s\n", queue[front]);

    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % MAX;
    }
}

// Ver siguiente orden
void verSiguiente() {
    if (estaVacia()) {
        printf("No hay órdenes.\n");
        return;
    }

    printf("Siguiente orden: %s\n", queue[front]);
}

// Ver última orden
void verUltima() {
    if (estaVacia()) {
        printf("No hay órdenes.\n");
        return;
    }

    printf("Última orden: %s\n", queue[rear]);
}

// Mostrar todas las órdenes (extra útil)
void mostrarCola() {
    if (estaVacia()) {
        printf("No hay órdenes en la cola.\n");
        return;
    }

    printf("Órdenes en espera:\n");
    int i = front;

    while (1) {
        printf("- %s\n", queue[i]);
        if (i == rear) break;
        i = (i + 1) % MAX;
    }
}

// Menú principal
int main() {
    int opcion;
    char orden[50];

    do {
        printf("\n--- SISTEMA DE COMANDAS (MAX 6) ---\n");
        printf("1. Recibir comanda\n");
        printf("2. Servir platillo\n");
        printf("3. Ver siguiente orden\n");
        printf("4. Ver última orden\n");
        printf("5. Mostrar todas las órdenes\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // limpiar buffer

        switch (opcion) {
            case 1:
                printf("Ingrese la orden: ");
                fgets(orden, 50, stdin);
                orden[strcspn(orden, "\n")] = 0;
                enqueue(orden);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                verSiguiente();
                break;

            case 4:
                verUltima();
                break;

            case 5:
                mostrarCola();
                break;

            case 6:
                printf("Saliendo del sistema...\n");
                break;

            default:
                printf("Opción inválida.\n");
        }

    } while (opcion != 6);

    return 0;
}
