#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];
    // TODO: Complete and document

    if (argc != 2) {
        printf("USAGE: parta FILEIN\n");
        return 1;
    }

    char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        printf("ERROR: %s not found\n", filename);
        return 2;
    }

    size_t upper = 0;
    size_t lower = 0;
    size_t number = 0;
    size_t space = 0;
    size_t other = 0;

    while (1) {
        ssize_t bytes_read = read(fd, buffer, BUFSIZE);
        if (bytes_read < 0) {
            close(fd);
            return 1;
        }
        if (bytes_read == 0) {
            break;
        }

        for (ssize_t i = 0; i < bytes_read; i++) {
            unsigned char c = (unsigned char)buffer[i];

            if (isupper(c)) {
                upper++;
            } else if (islower(c)) {
                lower++;
            } else if (isdigit(c)) {
                number++;
            } else if (isspace(c)) {
                space++;
            } else {
                other++;
            }
        }
    }

    close(fd);

    printf("Upper,%zu\n", upper);
    printf("Lower,%zu\n", lower);
    printf("Number,%zu\n", number);
    printf("Space,%zu\n", space);
    printf("Other,%zu\n", other);

    return 0;
}
