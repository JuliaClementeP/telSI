#include <stdio.h>
#include <stdlib.h>

// Función que reserva memoria dinámica para un array de floats
float* ReservaMemoria(int numvecinos) {
    float *p = NULL;

    // Reservar memoria dinámica
    p = (float*)malloc(sizeof(float) * numvecinos);
    // Alternativa: memoria inicializada a cero
    // p = (float*)calloc(numvecinos, sizeof(float));

    // Comprobar que la memoria se asignó correctamente
    if(p == NULL) {
        printf("\nError allocating memory\n");
    }

    // Devolver puntero al array
    return p;
}

int main() {
    int numvecinos, i;
    float *pvecinos, suma = 0;

    printf("\nEnter the number of people in the neighborhood: ");
    scanf("%d", &numvecinos);

    // Llamada a la función de reserva de memoria
    pvecinos = ReservaMemoria(numvecinos);
    if (pvecinos == NULL) return -1;

    // Leer datos y acumular
    for(i = 0; i < numvecinos; i++) {
        printf("\nIntroduce la cantidad del vecino %d: ", i + 1);
        scanf("%f", &pvecinos[i]);
        suma += pvecinos[i];
    }

    printf("Total: %f\n", suma);

    // Liberar memoria dinámica
    free(pvecinos);

    return 0;
}