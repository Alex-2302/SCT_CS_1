// caesar.c
// Simple Caesar cipher with separate encrypt() and decrypt() functions.
// Reads key (integer) and a line of text of arbitrary length from stdin.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Read a line of arbitrary length from stdin; caller must free the returned buffer.
   Returns NULL on EOF with no data. */
char *read_line(void) {
    size_t cap = 128;
    size_t len = 0;
    char *buf = malloc(cap);
    if (!buf) return NULL;

    int c;
    while ((c = getchar()) != EOF) {
        if (len + 1 >= cap) { // +1 for '\0'
            size_t newcap = cap * 2;
            char *tmp = realloc(buf, newcap);
            if (!tmp) { free(buf); return NULL; }
            buf = tmp;
            cap = newcap;
        }
        buf[len++] = (char)c;
        if (c == '\n') break;
    }

    if (len == 0 && c == EOF) { free(buf); return NULL; }

    buf[len] = '\0';
    // strip final newline (optional) — keep consistent with typical input
    if (len > 0 && buf[len-1] == '\n') buf[len-1] = '\0';
    return buf;
}

/* Normalize key to 0..25 */
int norm_key(int k) {
    k %= 26;
    if (k < 0) k += 26;
    return k;
}

/* Encrypt input string using Caesar shift key (0..25).
   Returns a newly allocated string (caller must free). */
char *encrypt(const char *in, int key) {
    if (!in) return NULL;
    key = norm_key(key);
    size_t n = strlen(in);
    char *out = malloc(n + 1);
    if (!out) return NULL;

    for (size_t i = 0; i < n; ++i) {
        unsigned char ch = (unsigned char)in[i];
        if (ch >= 'a' && ch <= 'z') {
            out[i] = (char)((((ch - 'a') + key) % 26) + 'a');
        } else if (ch >= 'A' && ch <= 'Z') {
            out[i] = (char)((((ch - 'A') + key) % 26) + 'A');
        } else {
            out[i] = ch;
        }
    }
    out[n] = '\0';
    return out;
}

/* Decrypt input string using Caesar shift key (0..25).
   Returns a newly allocated string (caller must free). */
char *decrypt(const char *in, int key) {
    // decryption is encryption with -key
    return encrypt(in, -key);
}

int main(void) {
    printf("Caesar cipher — separate encrypt() and decrypt().\n");

    // Read mode
    char mode;
    printf("Choose (e)ncrypt or (d)ecrypt: ");
    if (scanf(" %c", &mode) != 1) {
        fprintf(stderr, "Failed to read mode.\n");
        return 1;
    }
    mode = tolower((unsigned char)mode);
    if (mode != 'e' && mode != 'd') {
        fprintf(stderr, "Invalid mode. Use 'e' or 'd'.\n");
        return 1;
    }

    // Read key (integer)
    int key;
    printf("Enter key (integer, can be negative or >25): ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Failed to read key.\n");
        return 1;
    }

    // consume remaining newline after scanf so read_line works correctly
    int ch = getchar();
    (void)ch;

    // Read message (any length)
    printf("Enter text (press Enter when done):\n");
    char *text = read_line();
    if (!text) {
        fprintf(stderr, "No input text (EOF).\n");
        return 1;
    }

    char *out = NULL;
    if (mode == 'e') {
        out = encrypt(text, key);
        if (!out) { fprintf(stderr, "Memory error.\n"); free(text); return 1; }
        printf("\nEncrypted: %s\n", out);
    } else {
        out = decrypt(text, key);
        if (!out) { fprintf(stderr, "Memory error.\n"); free(text); return 1; }
        printf("\nDecrypted: %s\n", out);
    }

    free(text);
    free(out);
    return 0;
}
