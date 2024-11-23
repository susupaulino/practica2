#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Se necesita para la función time()

int main() {
    int i;

    // Mostrar el valor máximo que puede devolver rand()
    printf("RAND_MAX is %u\n", RAND_MAX);

    // Inicializar el generador de números aleatorios con la hora actual
    srand(time(0));

    // Imprimir 8 números aleatorios entre 0 y RAND_MAX
    printf("random values from 0 to RAND_MAX\n");
    for(i = 0; i < 8; i++) {
        printf("%d\n", rand());
    }

    // Imprimir 8 números aleatorios entre 1 y 20
    printf("random values from 1 to 20\n");
    for(i = 0; i < 8; i++) {
        printf("%d\n", (rand() % 20) + 1);
    }

    return 0;
}
