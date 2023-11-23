#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_BUFFER 16

void p(char *b, size_t s, size_t o) {
    printf("%08zx: ", o);

    bool n = false;
    for (size_t i = 0; i < s; i++) {
        if (n) break;
        else if (i < s - 1 && b[i] == '\\' && b[i + 1] == 'n') {
            putchar('0'); putchar('a');
            n = true; i++;
        } else {
            printf("%02x%c", b[i], (i % 2 == 1) ? ' ' : 0);
        }
    }

    size_t h = s;
    while (h < MAX_BUFFER) {
        putchar(' '); h++;
    }

    putchar(' ');

    n = false;

    for (size_t i = 0; i < s; i++) {
        if (n) break;
        else if (i < s - 1 && b[i] == '\\' && b[i + 1] == 'n') {
            putchar('.');
            n = true; i++;
        } else if (b[i] >= 32 && b[i] <= 126) {
            putchar(b[i]);
        } else {
            putchar('.');
        }
    }

    putchar('\n');
}

int main(int c, char *v[]) {
    FILE *f;
    char b[MAX_BUFFER];
    size_t s, o = 0;

    if (c != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", v[0]);
        return 1;
    }

    f = fopen(v[1], "rb");
    if (!f) { perror("Error opening file"); return 1; }

    while ((s = fread(b, 1, MAX_BUFFER, f)) > 0) {
        p(b, s, o);
        o += s;
    }

    fclose(f);
    return 0;
}
