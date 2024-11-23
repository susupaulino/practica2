#include <stdio.h>
#include <fcntl.h>

void display_flags(char *, unsigned int);
void binary_print(unsigned int);

int main(int argc, char *argv[]) {
    // Mostrar diferentes banderas de apertura de archivos y su representación binaria
    display_flags("O_RDONLY\t\t", O_RDONLY);
    display_flags("O_WRONLY\t\t", O_WRONLY);
    display_flags("O_RDWR\t\t\t", O_RDWR);
    printf("\n");
    display_flags("O_APPEND\t\t", O_APPEND);
    display_flags("O_TRUNC\t\t\t", O_TRUNC);
    display_flags("O_CREAT\t\t\t", O_CREAT);
    printf("\n");
    // Mostrar combinación de banderas
    display_flags("O_WRONLY|O_APPEND|O_CREAT", O_WRONLY|O_APPEND|O_CREAT);
}

void display_flags(char *label, unsigned int value) {
    // Muestra el nombre de la bandera y su valor en decimal y binario
    printf("%s\t: %d\t:", label, value);
    binary_print(value);
    printf("\n");
}

void binary_print(unsigned int value) {
    unsigned int mask = 0xff000000; // Comienza con una máscara para el byte más alto
    unsigned int shift = 256*256*256; // Desplazamiento para el byte más alto
    unsigned int byte, byte_iterator, bit_iterator;

    // Iterar sobre los 4 bytes del valor
    for(byte_iterator = 0; byte_iterator < 4; byte_iterator++) {
        byte = (value & mask) / shift; // Aislar cada byte
        printf(" ");
        // Imprimir los bits de cada byte
        for(bit_iterator = 0; bit_iterator < 8; bit_iterator++) {
            if(byte & 0x80) // Si el bit más alto no es 0
                printf("1"); // Imprimir 1
            else
                printf("0"); // Imprimir 0
            byte *= 2; // Mover todos los bits hacia la izquierda por 1
        }
        mask /= 256; // Mover los bits en la máscara a la derecha por 8
        shift /= 256; // Mover los bits en el desplazamiento a la derecha por 8
    }
}
