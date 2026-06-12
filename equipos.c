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
    int opcion;
    do {
        printf("\n=== SISTEMA DE CONTROL DE EQUIPOS ===\n");
        printf("1. Registrar equipos\n2. Mostrar equipos registrados\n3. Buscar equipo por codigo\n");
        printf("4. Modificar informacion de equipo\n5. Eliminar equipo\n6. Salir\n");
        printf("Seleccione una opcion: ");
        
        if (scanf("%d", &opcion) != 1) { limpiarBuffer(); opcion = 0; }

        switch(opcion) {
            case 1: printf("\nOpcion 1 en construccion...\n"); break;
            case 2: printf("\nOpcion 2 en construccion...\n"); break;
            case 3: printf("\nOpcion 3 en construccion...\n"); break;
            case 4: printf("\nOpcion 4 en construccion...\n"); break;
            case 5: printf("\nOpcion 5 en construccion...\n"); break;
            case 6: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while(opcion != 6);
    return 0;
}