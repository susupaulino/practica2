#include <stdio.h>
#include <stdlib.h>
#include "hacking.h"  // Include the hacking header

void usage(char *prog_name, char *filename) {
    printf("Usage: %s <data to add to %s>\n", prog_name, filename);
    exit(0);
}

int main(int argc, char *argv[]) {
    int fd;  // file descriptor
    char *buffer, *datafile;

    // Use the ec_malloc function from hacking.h to allocate memory safely
    buffer = (char *) ec_malloc(100);  // Allocating 100 bytes
    datafile = (char *) ec_malloc(20);  // Allocating 20 bytes

    strcpy(datafile, "/tmp/notes");

    if(argc < 2)  // If there aren't command-line arguments
        usage(argv[0], datafile);  // Display usage message and exit

    strcpy(buffer, argv[1]);  // Copy the data into the buffer
    printf("[DEBUG] buffer @ %p: \'%s\'\n", buffer, buffer);
    printf("[DEBUG] datafile @ %p: \'%s\'\n", datafile, datafile);

    // Open file and append data (same as before)
    fd = open(datafile, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if(fd == -1)
        fatal("in main() while opening file");  // Use fatal() from hacking.h to handle errors

    printf("[DEBUG] file descriptor is %d\n", fd);

    // Write data to the file
    if(write(fd, buffer, strlen(buffer)) == -1)
        fatal("in main() while writing buffer to file");

    // Close the file
    if(close(fd) == -1)
        fatal("in main() while closing file");

    printf("Note has been saved.\n");

    // Free the allocated memory
    free(buffer);
    free(datafile);

    return 0;
}


