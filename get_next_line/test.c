#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

char *getnextline(FILE *file) {
    static char buffer[BUFFER_SIZE];
    if (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        return buffer;
    } else {
        return NULL;
    }
}

#include <stdio.h>
#include <stdlib.h>

char *getnextline(FILE *file);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char *line;
    while ((line = getnextline(file)) != NULL) {
        printf("%s", line);
    }

    fclose(file);
    return 0;
}
//gcc test.c -o gnl 
//./gnl testfile.txt