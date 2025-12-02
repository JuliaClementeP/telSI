#ifndef FICHA2_H
#define FICHA2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAD 50

// Declaración de la estructura
typedef struct card2 {
    char *pnombre;   // Puntero a nombre dinámico
    float nota;      // Nota de la persona
} Ficha2;

// Prototipo de la función para añadir una estructura al array dinámico
int AnyadirUnaStruct(Ficha2 **pp, int num);

// Prototipo de función auxiliar para leer cadenas de forma segura
void LeeCadena(char *cad, int n);

#endif // FICHA2_H
