#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fecha {
    int dia;
    int mes;
    int anyo;
} tFecha;

typedef struct piso {
    char titular[40];
    unsigned int piso;
    char letra;
    float cantidad;
    tFecha f_ingreso;
} tPiso;


tPiso* ReservaMemoria(int n);
void LeePisos(tPiso* pPisos, int n);


int main() {
    int numpisos = -1;
    int leidos;
    char c;
    tPiso* pPisos = NULL;

    // Leer número de pisos de forma segura
    do {
        printf("\nNumber of flats: ");
        leidos = scanf("%d", &numpisos);
        while ((c = getchar()) != '\n' && c != EOF);  // limpiar buffer
    } while(leidos != 1 || numpisos < 0);

    // Invocar la función de reserva
    pPisos = ReservaMemoria(numpisos);
    if (pPisos == NULL) {
        printf("Error reservando memoria.\n");
        return -1;
    }

    // Leer los datos de los pisos
    LeePisos(pPisos, numpisos);

    // Mostrar los datos introducidos
    printf("\nListado de pisos:\n");
    for (int i = 0; i < numpisos; i++) {
        printf("%d. Titular: %s, Piso: %u%c, Cantidad: %.2f, Fecha: %02d/%02d/%04d\n",
               i + 1,
               pPisos[i].titular,
               pPisos[i].piso,
               pPisos[i].letra,
               pPisos[i].cantidad,
               pPisos[i].f_ingreso.dia,
               pPisos[i].f_ingreso.mes,
               pPisos[i].f_ingreso.anyo);
    }

    free(pPisos);  // liberar memoria
    return 0;
}




tPiso* ReservaMemoria(int n) {
    if (n <= 0) return NULL;
    tPiso* p = (tPiso*)calloc(n, sizeof(tPiso));
    return p;  // devuelve NULL si falla
}


void LeePisos(tPiso* pPisos, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nPiso %d\n", i + 1);

        printf("Titular: ");
        fgets(pPisos[i].titular, sizeof(pPisos[i].titular), stdin);
        // eliminar salto de línea si existe
        size_t len = strlen(pPisos[i].titular);
        if (len > 0 && pPisos[i].titular[len - 1] == '\n') {
            pPisos[i].titular[len - 1] = '\0';
        }

        printf("Número de piso: ");
        scanf("%u", &pPisos[i].piso);

        printf("Letra: ");
        scanf(" %c", &pPisos[i].letra);

        printf("Cantidad: ");
        scanf("%f", &pPisos[i].cantidad);

        printf("Fecha ingreso (día mes año): ");
        scanf("%d %d %d", &pPisos[i].f_ingreso.dia,
                          &pPisos[i].f_ingreso.mes,
                          &pPisos[i].f_ingreso.anyo);

        getchar(); // limpiar buffer para siguiente fgets
    }
}
