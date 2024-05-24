#include <stdio.h>

void write_public_key(unsigned int e, unsigned int n) {
    FILE *fptr;

    fptr = fopen("key_pub.txt", "w");

    if (fptr == NULL) {
        printf("Couldn't write public key file.");
        return;
    }

    fprintf(fptr, "%d, %d", e, n);
}

void write_private_key(unsigned int d, unsigned int n) {
    FILE *fptr;

    fptr = fopen("key_priv.txt", "w");

    if (fptr == NULL) {
        printf("Couldn't write private key file.");
        return;
    }

    fprintf(fptr, "%d, %d", d, n);
}
