#include <stdio.h>
#include <stdlib.h>

void printHexAndAscii(const unsigned char *buffer, size_t bytesRead, size_t offset) {
    printf("%08zx: ", offset); // Print the offset in hexadecimal

    // Print hex values in pairs
    for (size_t i = 0; i < 16; i += 2) {
        if (i < bytesRead) {
            printf("%02x", buffer[i]); // Print first byte of the pair
        } else {
            printf("  "); // Print spaces if less than 16 bytes were read
        }

        if (i + 1 < bytesRead) {
            printf("%02x", buffer[i + 1]); // Print second byte of the pair
        } else {
            printf("  "); // Print spaces if the second byte of the pair is missing
        }

        printf(" "); // Space between byte pairs, but no extra space after 8 bytes
    }

    printf(" ");
    for (size_t i = 0; i < bytesRead; i++) {
        if (buffer[i] >= 32 && buffer[i] <= 126)
            printf("%c", buffer[i]);
        else
            printf(".");
    }

    printf("\n");
}



int main(int argc, char *argv[]) {
    FILE *file;
    unsigned char buffer[16];
    size_t bytesRead, offset = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    while ((bytesRead = fread(buffer, 1, 16, file)) > 0) {
        printHexAndAscii(buffer, bytesRead, offset);
        offset += bytesRead; // Update the offset
    }

    fclose(file);
    return 0;
}
