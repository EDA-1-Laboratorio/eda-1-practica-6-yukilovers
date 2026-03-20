EJERCICIO 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Estructura de la Canción (Nodo)
typedef struct Cancion {
    char titulo[50];
    struct Cancion *sig;
    struct Cancion *ant;
} Cancion;

// 2. Estructura de la Playlist (Controlador)
typedef struct {
    Cancion *inicio;
    Cancion *fin;
} Playlist;

// Función para crear una canción nueva
Cancion* crearCancion(char* nombre) {
    Cancion* nueva = (Cancion*)malloc(sizeof(Cancion));
    strcpy(nueva->titulo, nombre);
    nueva->sig = NULL;
    nueva->ant = NULL;
    return nueva;
}

// Operación: Agregar al FINAL (Cola)
void agregarFinal(Playlist* lista, char* nombre) {
    Cancion* nueva = crearCancion(nombre);
    if (lista->inicio == NULL) {
        lista->inicio = lista->fin = nueva;
    } else {
        lista->fin->sig = nueva;
        nueva->ant = lista->fin;
        lista->fin = nueva;
    }
}

// Operación: Agregar al INICIO
void agregarInicio(Playlist* lista, char* nombre) {
    Cancion* nueva = crearCancion(nombre);
    if (lista->inicio == NULL) {
        lista->inicio = lista->fin = nueva;
    } else {
        nueva->sig = lista->inicio;
        lista->inicio->ant = nueva;
        lista->inicio = nueva;
    }
}

// Operación: Mostrar Playlist
void mostrarPlaylist(Playlist* lista) {
    Cancion* actual = lista->inicio;
    if (actual == NULL) {
        printf("\n[ La playlist está vacía ]\n");
        return;
    }
    printf("\n--- TU PLAYLIST ACTUAL ---\n");
    while (actual != NULL) {
        printf("🎵 %s\n", actual->titulo);
        actual = actual->sig;
    }
    printf("--------------------------\n");
}

int main() {
    Playlist miLista = {NULL, NULL};
    int opcion;
    char nombreCancion[50];

    do {
        printf("\n--- REPRODUCTOR C ---\n");
        printf("1. Agregar canción al inicio\n");
        printf("2. Agregar canción al final\n");
        printf("3. Ver playlist\n");
        printf("4. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el salto de línea del buffer

        if (opcion == 1 || opcion == 2) {
            printf("Escribe el nombre de la canción: ");
            fgets(nombreCancion, 50, stdin);
            nombreCancion[strcspn(nombreCancion, "\n")] = 0; // Quitar el enter al final

            if (opcion == 1) agregarInicio(&miLista, nombreCancion);
            else agregarFinal(&miLista, nombreCancion);
            printf("¡Añadida!\n");
        } 
        else if (opcion == 3) {
            mostrarPlaylist(&miLista);
        }

    } while (opcion != 4);

    printf("Saliendo del reproductor...\n");
    return 0;
}

