#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array = NULL;
    int inicial, total, i;

    // ① Pedir número de elementos iniciales
    printf("Número de elementos iniciales: ");
    scanf("%d", &inicial);

    // ② Reserva inicial con calloc (inicializa a cero)
    array = (int*)calloc(inicial, sizeof(int));
    if (array == NULL) {
        printf("Error al asignar memoria inicial\n");
        return -1;
    }

    // ③ Leer valores iniciales
    for (i = 0; i < inicial; i++) {
        printf("Elemento %d: ", i);
        scanf("%d", &array[i]);
    }

    // ④ Pedir número total de elementos después de redimensionar
    printf("Número total de elementos después de redimensionar: ");
    scanf("%d", &total);

    if (total < inicial) total = inicial; // evitar pérdida de datos

    // ⑤ Redimensionar array usando realloc con puntero temporal
    int *temp = (int*)realloc(array, total * sizeof(int));
    if (temp == NULL) {
        printf("Error al redimensionar memoria\n");
        free(array);  // liberar bloque original
        return -1;
    }
    array = temp;

    // ⑥ Inicializar los nuevos elementos a cero si se aumentó el tamaño
    for (i = inicial; i < total; i++) {
        array[i] = 0;
    }

    // ⑦ Mostrar todos los elementos
    printf("\nArray completo:\n");
    for (i = 0; i < total; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // ⑧ Liberar memoria
    free(array);

    return 0;
}
