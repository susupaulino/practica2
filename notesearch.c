#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h> // Para getuid() y lseek()
#include "hacking.h"

#define FILENAME "/var/notes"

// Prototipos de funciones
int print_notes(int, int, char *); // Nota de impresión.
int find_user_note(int, int); // Buscar una nota para un usuario.
int search_note(char *, char *); // Función de búsqueda de palabra clave.
void fatal(char *); // Manejador de errores fatales.

int main(int argc, char *argv[]) {
    int userid, printing = 1, fd; // Descriptor de archivo
    char searchstring[100];

    // Si hay un argumento, se utiliza como la cadena de búsqueda
    if (argc > 1) {
        strcpy(searchstring, argv[1]);
    } else { 
        searchstring[0] = 0; // Si no hay argumento, cadena vacía.
    }

    // Obtener el UID real
    userid = getuid();

    // Abrir el archivo de notas para lectura
    fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        fatal("in main() while opening file for reading");
    }

    // Imprimir notas que coincidan con el UID y la cadena de búsqueda
    while (printing) {
        printing = print_notes(fd, userid, searchstring);
    }

    printf("-------[ end of note data ]-------\n");
    close(fd); // Cerrar el archivo
}

// Función para imprimir las notas de un UID dado que coinciden con una cadena de búsqueda opcional.
// Devuelve 0 al final del archivo, 1 si hay más notas.
int print_notes(int fd, int uid, char *searchstring) {
    int note_length;
    char byte = 0, note_buffer[100];

    // Buscar la siguiente nota para el UID dado
    note_length = find_user_note(fd, uid);

    if (note_length == -1) { // Si se llega al final del archivo, retornar 0
        return 0;
    }

    // Leer los datos de la nota
    read(fd, note_buffer, note_length); 
    note_buffer[note_length] = 0; // Terminar la cadena de caracteres

    // Si la cadena de búsqueda está presente en la nota, imprimirla
    if (search_note(note_buffer, searchstring)) {
        printf(note_buffer); // Imprimir la nota
    }

    return 1;
}

// Función para buscar la siguiente nota para un UID dado.
// Devuelve -1 si se llega al final del archivo, de lo contrario, devuelve la longitud de la nota encontrada.
int find_user_note(int fd, int user_uid) {
    int note_uid = -1;
    unsigned char byte;
    int length;

    while (note_uid != user_uid) { // Loop hasta que se encuentre una nota para el UID del usuario.
        if (read(fd, &note_uid, 4) != 4) { // Leer los datos del UID.
            return -1; // Si no se leen 4 bytes, devolver código de final de archivo.
        }

        // Impresión de depuración para mostrar el UID leído
        printf("[DEBUG] Found UID: %d\n", note_uid);

        if (read(fd, &byte, 1) != 1) { // Leer el separador de nueva línea.
            return -1;
        }

        byte = length = 0;
        while (byte != '\n') { // Calcular cuántos bytes hay hasta el final de la línea.
            if (read(fd, &byte, 1) != 1) { // Leer un solo byte.
                return -1; // Si no se lee un byte, devolver código de final de archivo.
            }
            length++;
        }
    }

    // Retroceder en el archivo por la longitud de la nota para leerla correctamente
    lseek(fd, length * -1, SEEK_CUR);

    // Imprimir información de depuración sobre la nota encontrada
    printf("[DEBUG] found a %d byte note for user id %d\n", length, note_uid);
    return length;
}

// Función para buscar una palabra clave dentro de una nota dada.
// Devuelve 1 si se encuentra una coincidencia, 0 si no se encuentra.
int search_note(char *note, char *keyword) {
    int i, keyword_length, match = 0;
    keyword_length = strlen(keyword);

    // Si no hay una cadena de búsqueda, siempre se "encuentra" (siempre coincide)
    if (keyword_length == 0) {
        return 1;
    }

    // Iterar sobre los bytes de la nota
    for (i = 0; i < strlen(note); i++) {
        if (note[i] == keyword[match]) { // Si el byte coincide con el de la palabra clave
            match++; // Continuar con la coincidencia
        } else {
            if (note[i] == keyword[0]) { // Si el byte coincide con el primer byte de la palabra clave
                match = 1; // Comenzar de nuevo la búsqueda
            } else {
                match = 0; // Si no coincide, reiniciar el contador de coincidencias
            }
        }

        // Si hay una coincidencia completa, devolver 1
        if (match == keyword_length) {
            return 1;
        }
    }

    // Si no se encontró ninguna coincidencia
    return 0;
}
