#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void printHexAndAscii(const unsigned char *buffer, size_t bytesRead, size_t offset) {
    printf("%08zx: ", offset);

    // Print the hex values grouped
    bool newlineEncountered = false;
    for (size_t i = 0; i < bytesRead; i++) {
        if (newlineEncountered) {
            break;
        } else if (i < bytesRead - 1 && buffer[i] == '\\' && buffer[i + 1] == 'n') {
            printf("0a "); // Print 0a for newline
            newlineEncountered = true;
            i++; // Skip the 'n' character
        } else {
            printf("%02x", buffer[i]);
            if (i % 2 == 1) {
                printf(" "); // Add a space after every 2 characters
            }
        }
    }

    // Add extra spaces for alignment
    size_t hexPrinted = bytesRead;
    while (hexPrinted < 16) {
        printf("   ");
        hexPrinted++;
    }

    printf(" ");

    // Reset newline detection flag for ASCII part
    newlineEncountered = false;

    // Print the ASCII characters
    for (size_t i = 0; i < bytesRead; i++) {
        if (newlineEncountered) {
            break;
        } else if (i < bytesRead - 1 && buffer[i] == '\\' && buffer[i + 1] == 'n') {
            printf("."); // Interpret '\n' as a newline character and print '.'
            newlineEncountered = true;
            i++; // Skip the 'n' character
        } else if (buffer[i] >= 32 && buffer[i] <= 126) {
            printf("%c", buffer[i]);
        } else {
            printf(".");
        }
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
