#include <stdio.h>
#include <stdlib.h>
#define MAX_HORAS 24  // número máximo de horas por día
/*
 * unit9_sol_ej5.c
 * lectura y almacenamiento de temperaturas horarias de una estación meteorológica
 * usando un array dinámico bidimensional de temperaturas.
 * Cada fila corresponde a un día y cada columna a una hora del día.
 */

/* Función para leer los datos de temperatura */
void LeerTemperaturas(float **mat, int filas, int columnas) {
    int i, j;
    for (i = 0; i < filas; i++) {
        printf("Temperaturas del día %d:\n", i + 1);
        for (j = 0; j < columnas; j++) {
            printf("  Hora %d: ", j + 1);
            scanf("%f", &mat[i][j]);
        }
    }
}

/* Función para mostrar la matriz de temperaturas */
void MostrarTemperaturas(float **mat, int filas, int columnas) {
    int i, j;
    printf("\nMatriz de temperaturas:\n");
    for (i = 0; i < filas; i++) {
        printf("Día %d: ", i + 1);
        for (j = 0; j < columnas; j++) {
            printf("%.1f ", mat[i][j]);
        }
        printf("\n");
    }
}

/* Función para liberar la memoria de la matriz */
void LiberarMatriz(float **mat, int filas) {
    int i;
    for (i = 0; i < filas; i++) {
        free(mat[i]);   // liberar cada fila
        mat[i] = NULL;  // buena práctica: evitar punteros colgantes
    }
    free(mat);         // liberar el array de punteros
    mat = NULL;
}

int main() {
    float **temperaturas = NULL;
    int nDias, nHoras;
    int i;

    /* Pedir número de días y horas */
    do {
        printf("Número de días: ");
        scanf("%d", &nDias);
    } while (nDias < 1);

    do {
        printf("Número de horas por día (máx %d): ", MAX_HORAS);
        scanf("%d", &nHoras);
    } while (nHoras < 1 || nHoras > MAX_HORAS);

    /* Reservar memoria para el array de punteros (filas) */
    temperaturas = (float **)malloc(sizeof(float *) * nDias);
    if (temperaturas == NULL) {
        printf("Error: memoria insuficiente.\n");
        return 1;
    }

    /* Reservar memoria para cada fila (columnas) */
    for (i = 0; i < nDias; i++) {
        temperaturas[i] = (float *)malloc(sizeof(float) * nHoras);
        if (temperaturas[i] == NULL) {
            printf("Error: memoria insuficiente para la fila %d.\n", i + 1);
            nDias = i;  // ajustar número de filas válidas
            break;
        }
    }

    /* Leer las temperaturas */
    LeerTemperaturas(temperaturas, nDias, nHoras);

    /* Mostrar las temperaturas */
    MostrarTemperaturas(temperaturas, nDias, nHoras);

    /* Liberar la memoria */
    LiberarMatriz(temperaturas, nDias);

    return 0;
}