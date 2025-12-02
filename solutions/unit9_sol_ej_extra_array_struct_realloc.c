#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAD 50

typedef struct card2 {
    char *pnombre;   
    float nota;      
} Ficha2;


void LeeCadena(char *cad, int n);
int AnyadirUnaStruct(Ficha2 **pp, int num);


int main() {
    int n = 0, i;
    char respuesta;
    Ficha2 *pFichas = NULL;

    // Bucle para añadir varias personas
    do {
        n = AnyadirUnaStruct(&pFichas, n);

        printf("¿Desea añadir otra persona? (s/n): ");
        scanf(" %c", &respuesta);
        while (getchar() != '\n');  // limpiar buffer
    } while (respuesta == 's' || respuesta == 'S');

    // Mostrar todas las personas añadidas
    printf("\nListado de personas:\n");
    for (i = 0; i < n; i++) {
        printf("%d. Nombre: %s, Nota: %.2f\n", i+1, pFichas[i].pnombre, pFichas[i].nota);
    }

    // Liberar memoria dinámica
    for (i = 0; i < n; i++) {
        free(pFichas[i].pnombre);
    }
    free(pFichas);

    return 0;
}

void LeeCadena(char *cad, int n) {
    fgets(cad, n, stdin);
    size_t len = strlen(cad);
    if (len > 0 && cad[len-1] == '\n') cad[len-1] = '\0';
}

int AnyadirUnaStruct(Ficha2 **pp, int num) {
    char string1[MAX_CAD];
    Ficha2 *pAux;

    printf("\nNombre? ");
    LeeCadena(string1, MAX_CAD);

    // Redimensionar array dinámico
    pAux = (Ficha2 *)realloc(*pp, sizeof(Ficha2) * (num + 1));

    if (pAux != NULL) {
        // Actualizar puntero si cambia de dirección
        *pp = pAux;

        // Reservar memoria para el nombre
        pAux[num].pnombre = (char *)malloc(strlen(string1) + 1);
        strcpy(pAux[num].pnombre, string1);

        // Leer nota
        printf("Nota? ");
        scanf("%f", &pAux[num].nota);
        while (getchar() != '\n');  // limpiar buffer

        // Incrementar contador
        num++;
    } else {
        printf("Error allocating memory.\n");
    }

    return num;
}
