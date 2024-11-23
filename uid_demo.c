#include <stdio.h>
#include <unistd.h>  // Necesario para getuid() y geteuid()

int main() {
    // Mostrar el UID real y el UID efectivo
    printf("real uid: %d\n", getuid());
    printf("effective uid: %d\n", geteuid());
    return 0;
}
