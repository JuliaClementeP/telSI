#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_COCHES 5
#define MAX_MARCA 20
#define MAX_MODELO 50

typedef struct {
    char marca[MAX_MARCA];
    char *modelo;   // Memoria dinámica
    float precio;
} tCoche;

void LeeCadena(char *cad, int n);
int CargarCoches(tCoche *pCoches[]);
void LiberarCoches(tCoche *pCoches[]);

int main() {
    tCoche *pCoches[NUM_COCHES] = {NULL};
    int i;

    // ① Cargar coches
    if (!CargarCoches(pCoches)) {
        printf("\n Error cargando coches. Abortando.\n");
        return 1;
    }

    // ② Mostrar coches
    printf("\nCoches introducidos:\n");
    for (i = 0; i < NUM_COCHES; i++) {
        printf("%d. Marca: %s, Modelo: %s, Precio: %.2f\n",
               i+1,
               pCoches[i]->marca,
               pCoches[i]->modelo,
               pCoches[i]->precio);
    }

    // ③ Liberar memoria
    LiberarCoches(pCoches);
    return 0;
}


void LeeCadena(char *cad, int n) {
    size_t len;

    fgets(cad, n, stdin);
    len = strlen(cad);

    if (len > 0 && cad[len - 1] == '\n')
        cad[len - 1] = '\0';
}

/*
   Devuelve:
      1  -> todo OK
      0  -> error (se libera lo reservado)
*/

int CargarCoches(tCoche *pCoches[]) {
    char buffer[MAX_MODELO];
    int i;

    for (i = 0; i < NUM_COCHES; i++) {

        // Reservar estructura
        pCoches[i] = malloc(sizeof(tCoche));
        if (pCoches[i] == NULL) {
            printf("Error reservando memoria para estructura %d\n", i);
            LiberarCoches(pCoches);
            return 0;
        }

        // Leer marca
        printf("Marca: ");
        LeeCadena(pCoches[i]->marca, MAX_MARCA);

        // Leer modelo
        printf("Modelo: ");
        LeeCadena(buffer, MAX_MODELO);

        // Reservar memoria para el modelo
        pCoches[i]->modelo = malloc(strlen(buffer) + 1);
        if (pCoches[i]->modelo == NULL) {
            printf("Error reservando memoria para modelo %d\n", i);
            LiberarCoches(pCoches);
            return 0;
        }

        strcpy(pCoches[i]->modelo, buffer);

        // Leer precio
        printf("Precio: ");
        scanf("%f", &pCoches[i]->precio);
        while (getchar() != '\n'); // limpiar buffer
    }

    return 1; // OK
}

void LiberarCoches(tCoche *pCoches[]) {
    int i;

    for (int i = 0; i < NUM_COCHES; i++) {
        if (pCoches[i] != NULL) {
            free(pCoches[i]->modelo);
            free(pCoches[i]);
            pCoches[i] = NULL;
        }
    }
}
