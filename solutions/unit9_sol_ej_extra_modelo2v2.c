#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void LeeCadena(char *cad, int n);
void aMayusculas(char *cad);
int empiezaPorVocal(const char *cad);
void LiberarTodo(char *pp[], int n);

int main() {
    char *pp[3], *tmp;
    char string[100];
    int i, j, idxMax = 0;
    int contadorVocal = 0, nFilas = 3;

    // Lectura y reserva dinámica con control de error
    for (i = 0; i < nFilas; i++) {
        printf("Cadena %d: ", i + 1);
        LeeCadena(string, 80);

        pp[i] = (char *)malloc(strlen(string) + 1);

        if (pp[i] == NULL) {
            printf("ERROR: No hay memoria (posición %d).\n", i);

            // Liberar lo reservado hasta ahora
            for (j = 0; j < i; j++)
                free(pp[j]);

            return 1;   // salir del programa de forma limpia
        }

        strcpy(pp[i], string);
    }

    // Intercambiar punteros pp[0] ↔ pp[2]
    tmp = pp[0];
    pp[0] = pp[2];
    pp[2] = tmp;

    // Encontrar cadena más larga y sustituir por: "CAMBIADA"
    for (i = 1; i < nFilas; i++) {
        if (strlen(pp[i]) > strlen(pp[idxMax])) {
            idxMax = i;
        }
    }

    free(pp[idxMax]);
    pp[idxMax] = (char *)malloc(strlen("CAMBIADA") + 1);

    if (pp[idxMax] == NULL) {
        printf("ERROR: No hay memoria reemplazando cadena.\n");

        // liberar todo antes de salir
        LiberarTodo(pp, nFilas);

        return 1;
    }

    strcpy(pp[idxMax], "CAMBIADA");

    // Convertir todas las cadenas a mayúsculas
    for (i = 0; i < nFilas; i++)
        aMayusculas(pp[i]);

    // Contar cadenas que empiezan por vocal
    for (i = 0; i < nFilas; i++) {
        if (empiezaPorVocal(pp[i]))
            contadorVocal++;
    }

    printf("\nCadenas finales:\n");
    for (i = 0; i < nFilas; i++)
        printf("%s\n", pp[i]);

    printf("\nCadenas que empiezan por vocal: %d\n", contadorVocal);

    // Liberar memoria dinámica
    for (i = 0; i < nFilas; i++) {
        free(pp[i]);
        pp[i] = NULL;
    }

    return 0;
}


// Leer cadena segura
void LeeCadena(char *cad, int n) {
    fgets(cad, n, stdin);
    size_t len = strlen(cad);
    if (len > 0 && cad[len - 1] == '\n')
        cad[len - 1] = '\0';
}

// Convertir cadena a mayúsculas
void aMayusculas(char *cad) {
    int i;

    for (i = 0; cad[i] != '\0'; i++)
        cad[i] = toupper(cad[i]);
}

// Comprobar vocal inicial
int empiezaPorVocal(const char *cad) {
    char c;

    if (cad[0] == '\0')
        return 0;

    c = toupper(cad[0]);
    return (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

// Liberar memoria
void LiberarTodo(char *pp[], int n) {
    for (int i = 0; i < n; i++) {
        free(pp[i]);
        pp[i] = NULL;
    }
}
