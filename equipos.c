#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int codigo;
    char nombre[50];
    char marca[50];
    char responsable[50];
    char estado[20];
    float precio;
} Equipo;

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int esSoloLetras(char cadena[]) {
    if (strlen(cadena) == 0) return 0; 
    for (int i = 0; i < strlen(cadena); i++) {
        if (!isalpha(cadena[i]) && cadena[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

int main() {
    return 0;
}