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

void registrarEquipo() {
    FILE *archivo = fopen("equipos.dat", "ab");
    if (!archivo) { printf("Error abriendo el archivo.\n"); return; }

    Equipo eq;
    memset(&eq, 0, sizeof(Equipo));

    printf("\n--- REGISTRAR EQUIPO ---\n");
    
    printf("Codigo: ");
    while(scanf("%d", &eq.codigo) != 1) { 
        limpiarBuffer(); 
        printf("Error: Ingrese solo digitos validos: "); 
    }
    limpiarBuffer();

    do {
        printf("Nombre del equipo: ");
        fgets(eq.nombre, 50, stdin); eq.nombre[strcspn(eq.nombre, "\n")] = 0;
        if (!esSoloLetras(eq.nombre)) printf("Error: Ingrese solo letras.\n");
    } while (!esSoloLetras(eq.nombre));

    do {
        printf("Marca: ");
        fgets(eq.marca, 50, stdin); eq.marca[strcspn(eq.marca, "\n")] = 0;
        if (!esSoloLetras(eq.marca)) printf("Error: Ingrese solo letras.\n");
    } while (!esSoloLetras(eq.marca));
    
    do {
        printf("Responsable asignado: ");
        fgets(eq.responsable, 50, stdin); eq.responsable[strcspn(eq.responsable, "\n")] = 0;
        if (!esSoloLetras(eq.responsable)) printf("Error: Ingrese solo letras.\n");
    } while (!esSoloLetras(eq.responsable));
    
    do {
        printf("Estado: ");
        fgets(eq.estado, 20, stdin); eq.estado[strcspn(eq.estado, "\n")] = 0;
        if (!esSoloLetras(eq.estado)) printf("Error: Ingrese solo letras.\n");
    } while (!esSoloLetras(eq.estado));

    printf("Precio: ");
    while(scanf("%f", &eq.precio) != 1) { 
        limpiarBuffer(); 
        printf("Error: Ingrese un precio valido. Precio: "); 
    }
    limpiarBuffer();

    fwrite(&eq, sizeof(Equipo), 1, archivo);
    fclose(archivo);
    printf("Equipo registrado exitosamente en archivo.\n");
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
            case 1: registrarEquipo(); break;
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