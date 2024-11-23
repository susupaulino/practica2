#ifndef HACKING_H
#define HACKING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>  // Para open(), O_WRONLY, O_CREAT, O_APPEND
#include <sys/stat.h> // Para S_IRUSR, S_IWUSR
#include <unistd.h>  // Para close()

// A function to display an error message and then exit
void fatal(char *message) {
    char error_message[100];
    strcpy(error_message, "[!!] Fatal Error ");
    strncat(error_message, message, 83);
    perror(error_message);
    exit(-1);
}

// An error-checked malloc() wrapper function
void *ec_malloc(unsigned int size) {
    void *ptr;
    ptr = malloc(size);
    if(ptr == NULL)
        fatal("in ec_malloc() on memory allocation");
    return ptr;
}

#endif // HACKING_H
