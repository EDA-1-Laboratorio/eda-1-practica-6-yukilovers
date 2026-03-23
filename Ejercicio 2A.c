#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Cola
char queue[MAX][50];
int front = -1, rear = -1;

// Enqueue (recibir comanda)
void enqueue(char orden[]) {
    if (rear == MAX - 1) {
        printf("La cola está llena.\n");
        return;
    }
    if (front == -1) front = 0;

    rear++;
    strcpy(queue[rear], orden);
    printf("Orden recibida: %s\n", orden);
}

// Dequeue (servir platillo)
void dequeue() {
    if (front == -1 || front > rear) {
        printf("No hay órdenes por servir.\n");
        return;
    }

    printf("Sirviendo: %s\n", queue[front]);
    front++;
}

// Consultar siguiente orden
void verSiguiente() {
    if (front == -1 || front > rear) {
        printf("No hay órdenes.\n");
        return;
    }
    printf("Siguiente orden: %s\n", queue[front]);
}

// Consultar última orden
void verUltima() {
    if (rear == -1) {
        printf("No hay órdenes.\n");
        return;
    }
    printf("Última orden: %s\n", queue[rear]);
}

// Menú principal
int main() {
    int opcion;
    char orden[50];

    do {
        printf("\n--- SISTEMA DE COMANDAS ---\n");
        printf("1. Recibir comanda\n");
        printf("2. Servir platillo\n");
        printf("3. Ver siguiente orden\n");
        printf("4. Ver última orden\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // limpiar buffer

        switch (opcion) {
            case 1:
                printf("Ingrese la orden: ");
                fgets(orden, 50, stdin);
                orden[strcspn(orden, "\n")] = 0; // quitar salto de línea
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
                printf("Saliendo...\n");
                break;

            default:
                printf("Opción inválida.\n");
        }

    } while (opcion != 5);

    return 0;
}
