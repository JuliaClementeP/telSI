#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITULO 100

typedef struct {
    char *titulo;
    float precio;
} tLibro;

void LeeCadena(char *cad, int n);
void AñadirLibros(tLibro **ppLibros, int *numLibros, int cantidad);

int main() {
    tLibro *pLibros = NULL;
    int i, n = 0;

    // ① Añadir 2 libros
    AñadirLibros(&pLibros, &n, 2);

    // ② Mostrar todos los libros
    printf("\nLibros añadidos:\n");
    for (i = 0; i < n; i++) {
        printf("%d. Título: %s | Precio: %.2f\n", i + 1, pLibros[i].titulo, pLibros[i].precio);
    }

    // ③ Liberar memoria
    for (i = 0; i < n; i++) {
        free(pLibros[i].titulo);
    }
    free(pLibros);

    return 0;
}

void LeeCadena(char *cad, int n) {
    fgets(cad, n, stdin);
    size_t len = strlen(cad);
    if (len > 0 && cad[len - 1] == '\n') cad[len - 1] = '\0';
}

void AñadirLibros(tLibro **ppLibros, int *numLibros, int cantidad) {
    int i;
    char buffer[MAX_TITULO];
    tLibro *pAux;

    // Redimensionar array dinámico
    pAux = (tLibro *)realloc(*ppLibros, sizeof(tLibro) * (*numLibros + cantidad));
    if (pAux == NULL) {
        printf("Error al asignar memoria.\n");
        return;
    }
    *ppLibros = pAux;

    // Leer datos de los nuevos libros
    for (i = 0; i < cantidad; i++) {
        printf("\nTítulo del libro %d: ", *numLibros + 1);
        getchar(); // limpiar buffer de entrada
        LeeCadena(buffer, MAX_TITULO);

        // Reservar memoria para el título
        (*ppLibros)[*numLibros].titulo = (char *)malloc(strlen(buffer) + 1);
        if ((*ppLibros)[*numLibros].titulo == NULL) {
            printf("Error al asignar memoria para el título.\n");
            return;
        }
        strcpy((*ppLibros)[*numLibros].titulo, buffer);

        // Leer precio
        printf("Precio del libro %d: ", *numLibros + 1);
        scanf("%f", &(*ppLibros)[*numLibros].precio);

        (*numLibros)++;
    }
}
