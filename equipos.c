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
void mostrarEquipos() {
    FILE *archivo = fopen("equipos.dat", "rb");
    if (!archivo) { printf("\nNo hay equipos registrados.\n"); return; }

    Equipo eq;
    printf("\n--- EQUIPOS REGISTRADOS ---\n");
    while (fread(&eq, sizeof(Equipo), 1, archivo)) {
        printf("Codigo: %d | Nombre: %s | Marca: %s | Resp: %s | Est: %s | Prec: %.2f\n", 
               eq.codigo, eq.nombre, eq.marca, eq.responsable, eq.estado, eq.precio);
    }
    fclose(archivo);
}

void buscarEquipo() {
    FILE *archivo = fopen("equipos.dat", "rb");
    if (!archivo) { printf("\nNo hay datos.\n"); return; }

    int codBuscado, encontrado = 0;
    Equipo eq;
    printf("\nIngrese el codigo a buscar: ");
    while(scanf("%d", &codBuscado) != 1) { limpiarBuffer(); printf("Error: Ingrese solo digitos validos: "); }
    limpiarBuffer();

    while (fread(&eq, sizeof(Equipo), 1, archivo)) {
        if (eq.codigo == codBuscado) {
            printf("\nEQUIPO ENCONTRADO:\n");
            printf("Nombre: %s\nMarca: %s\nResponsable: %s\nEstado: %s\nPrecio: %.2f\n", 
                   eq.nombre, eq.marca, eq.responsable, eq.estado, eq.precio);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) printf("Equipo no encontrado.\n");
    fclose(archivo);
}
void modificarEquipo() {
    FILE *archivo = fopen("equipos.dat", "r+b");
    if (!archivo) { printf("\nNo hay datos para modificar.\n"); return; }

    int codBuscado, encontrado = 0;
    Equipo eq;
    printf("\nIngrese el codigo del equipo a modificar: ");
    while(scanf("%d", &codBuscado) != 1) { limpiarBuffer(); printf("Error: Ingrese solo digitos validos: "); }
    limpiarBuffer();

    while (fread(&eq, sizeof(Equipo), 1, archivo)) {
        if (eq.codigo == codBuscado) {
            printf("Modificando equipo %s...\n", eq.nombre);
            
            do {
                printf("Nuevo Responsable: ");
                fgets(eq.responsable, 50, stdin); eq.responsable[strcspn(eq.responsable, "\n")] = 0;
                if (!esSoloLetras(eq.responsable)) printf("Error: Ingrese solo letras.\n");
            } while (!esSoloLetras(eq.responsable));

            do {
                printf("Nuevo Estado: ");
                fgets(eq.estado, 20, stdin); eq.estado[strcspn(eq.estado, "\n")] = 0;
                if (!esSoloLetras(eq.estado)) printf("Error: Ingrese solo letras.\n");
            } while (!esSoloLetras(eq.estado));
            
            fseek(archivo, -sizeof(Equipo), SEEK_CUR); 
            fwrite(&eq, sizeof(Equipo), 1, archivo);
            encontrado = 1;
            printf("Equipo modificado con exito.\n");
            break;
        }
    }
    if (!encontrado) printf("Equipo no encontrado.\n");
    fclose(archivo);
}

void eliminarEquipo() {
    FILE *archivo = fopen("equipos.dat", "rb");
    if (!archivo) { printf("\nNo hay datos.\n"); return; }
    
    FILE *temp = fopen("temp.dat", "wb");
    int codBuscado, encontrado = 0;
    Equipo eq;

    printf("\nIngrese el codigo del equipo a eliminar: ");
    while(scanf("%d", &codBuscado) != 1) { limpiarBuffer(); printf("Error: Ingrese solo digitos validos: "); }
    limpiarBuffer();

    while (fread(&eq, sizeof(Equipo), 1, archivo)) {
        if (eq.codigo == codBuscado) {
            encontrado = 1;
        } else {
            fwrite(&eq, sizeof(Equipo), 1, temp); 
        }
    }
    fclose(archivo);
    fclose(temp);

    remove("equipos.dat");
    rename("temp.dat", "equipos.dat");

    if (encontrado) printf("Equipo eliminado exitosamente.\n");
    else printf("Equipo no encontrado.\n");
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
            case 2: mostrarEquipos(); break;
            case 3: buscarEquipo(); break;
            case 4: modificarEquipo(); break;
            case 5: eliminarEquipo(); break;
            case 6: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while(opcion != 6);
    return 0;
}