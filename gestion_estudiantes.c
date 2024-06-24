#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define FILE_NAME "estudiantes.txt"

typedef struct {
    char nombre[MAX_NAME_LENGTH];
    int edad;
    float calificacion;
} Estudiante;

void agregarEstudiante();
void listarEstudiantes();
void buscarEstudiante();
void limpiarBuffer();

int main() {
    int opcion;
    
    while (1) {
        printf("Bienvenido al sistema de gestion de estudiantes.\n");
        printf("Menu:\n");
        printf("1. Agregar estudiante\n");
        printf("2. Listar estudiantes\n");
        printf("3. Buscar estudiante\n");
        printf("4. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        limpiarBuffer();  // Limpiar el búfer después de leer la opción
        
        switch(opcion) {
            case 1:
                agregarEstudiante();
                break;
            case 2:
                listarEstudiantes();
                break;
            case 3:
                buscarEstudiante();
                break;
            case 4:
                exit(0);
            default:
                printf("Opcion no valida.\n");
        }
    }
    
    return 0;
}

void agregarEstudiante() {
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        perror("No se puede abrir el archivo");
        return;
    }
    
    Estudiante estudiante;
    
    printf("Ingrese el nombre del estudiante: ");
    fgets(estudiante.nombre, MAX_NAME_LENGTH, stdin);
    estudiante.nombre[strcspn(estudiante.nombre, "\n")] = '\0';  // Eliminar el carácter de nueva línea

    printf("Ingrese la edad del estudiante: ");
    scanf("%d", &estudiante.edad);
    limpiarBuffer();  // Limpiar el búfer después de leer la edad

    printf("Ingrese la calificacion del estudiante: ");
    scanf("%f", &estudiante.calificacion);
    limpiarBuffer();  // Limpiar el búfer después de leer la calificación
    
    fprintf(file, "%s,%d,%.2f\n", estudiante.nombre, estudiante.edad, estudiante.calificacion);
    fclose(file);
    
    printf("Estudiante agregado con exito.\n");
}

void listarEstudiantes() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        perror("No se puede abrir el archivo");
        return;
    }
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Estudiante estudiante;
        sscanf(line, "%[^,],%d,%f", estudiante.nombre, &estudiante.edad, &estudiante.calificacion);
        printf("Nombre: %s, Edad: %d, Calificacion: %.2f\n", estudiante.nombre, estudiante.edad, estudiante.calificacion);
    }
    
    fclose(file);
}

void buscarEstudiante() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        perror("No se puede abrir el archivo");
        return;
    }
    
    char nombre[MAX_NAME_LENGTH];
    printf("Ingrese el nombre del estudiante a buscar: ");
    fgets(nombre, MAX_NAME_LENGTH, stdin);
    nombre[strcspn(nombre, "\n")] = '\0';  // Eliminar el carácter de nueva línea
    
    char line[256];
    int encontrado = 0;
    while (fgets(line, sizeof(line), file)) {
        Estudiante estudiante;
        sscanf(line, "%[^,],%d,%f", estudiante.nombre, &estudiante.edad, &estudiante.calificacion);
        if (strcmp(estudiante.nombre, nombre) == 0) {
            printf("Nombre: %s, Edad: %d, Calificacion: %.2f\n", estudiante.nombre, estudiante.edad, estudiante.calificacion);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Estudiante no encontrado.\n");
    }
    
    fclose(file);
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
