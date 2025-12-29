#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void LeeCadena(char *cad, int n);
void aMayusculas(char *cad);
int empiezaPorVocal(const char *cad);

int main() {
    char *pp[3];
    char *tmp;
    char string[100];
    int i, nFilas = 3, idxMax = 0, contadorVocal = 0;

    // Lectura y reserva dinámica -> solución poco segura
    for (i = 0; i < nFilas; i++) {
        printf("Cadena %d: ", i + 1);
        LeeCadena(string, 80);
        pp[i] = (char *)malloc(strlen(string) + 1);
        if (pp[i] != NULL)
            strcpy(pp[i], string);
    }

    tmp = pp[0];
    pp[0] = pp[2];
    pp[2] = tmp;


    for(i = 1; i < nFilas; i++) {
        if(strlen(pp[i]) > strlen(pp[idxMax])) {
            idxMax = i;
        }
    }

    free(pp[idxMax]);
    pp[idxMax] = (char*)malloc(strlen("CAMBIADA") + 1);
    if(pp[idxMax] != NULL)
        strcpy(pp[idxMax], "CAMBIADA");

    for(i = 0; i < nFilas; i++)
        aMayusculas(pp[i]);


    for(i = 0; i < nFilas; i++) {
        if(empiezaPorVocal(pp[i]))
            contadorVocal++;
    }

    printf("\nCadenas finales:\n");
    for(i = 0; i < nFilas; i++)
        printf("%s\n", pp[i]);

    printf("\nCadenas que empiezan por vocal: %d\n", contadorVocal);

    for(i = 0; i < nFilas; i++) {
        free(pp[i]);
        pp[i] = NULL;
    }

    return 0;
}

// Leer cadena segura
void LeeCadena(char *cad, int n) {
    fgets(cad, n, stdin);
    size_t len = strlen(cad);
    if(len > 0 && cad[len-1] == '\n')
        cad[len-1] = '\0';
}

// Convertir cadena a mayúsculas
void aMayusculas(char *cad) {
    for(int i = 0; cad[i] != '\0'; i++)
        cad[i] = toupper(cad[i]);
}

// Comprobar primera vocal
int empiezaPorVocal(const char *cad) {
    if(cad[0] == '\0') return 0;
    char c = toupper(cad[0]);
    return (c=='A' || c=='E' || c=='I' || c=='O' || c=='U');
}
