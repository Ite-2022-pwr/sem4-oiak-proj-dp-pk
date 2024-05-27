#include <stdio.h>

extern void encrypt(unsigned int d, unsigned int n);
extern void decrypt(unsigned int e, unsigned int n);

void write_public_key(unsigned int e, unsigned int n) {
    FILE *fptr;

    fptr = fopen("key_pub.txt", "w");

    if (fptr == NULL) {
        printf("Couldn't write public key file.");
        return;
    }

    fprintf(fptr, "%d,%d", e, n);
    fclose(fptr);
}

void write_private_key(unsigned int d, unsigned int n) {
    FILE *fptr;

    fptr = fopen("key_priv.txt", "w");

    if (fptr == NULL) {
        printf("Couldn't write private key file.");
        return;
    }

    fprintf(fptr, "%d,%d", d, n);
    fclose(fptr);
}

void read_private_key() {
    FILE *fptr;
    char buffer[100];
    int d,n;

    fptr = fopen("key_priv.txt", "r");
    if (fptr == NULL) {
        printf("Couldn't write private key file.");
        return;
    }

    if(fgets(buffer, sizeof(buffer), fptr) != NULL) {
        if(sscanf(buffer, "%d,%d", &d, &n) == 2) {
            printf("e: %d\n", d);
            printf("n: %d\n", n);
        } else {
            fprintf(stderr, "Error parsing values\n");
            fclose(fptr);
            return;
        }
    } else {
        fprintf(stderr, "Error reading file\n");
        fclose(fptr);
        return;
    }
    fclose(fptr);
    encrypt(d, n);
    return;
}

void read_public_key() {
    FILE *fptr;
    char buffer[100];
    int e,n;

    fptr = fopen("key_pub.txt", "r");
    if (fptr == NULL) {
        printf("Couldn't write public key file.");
        return;
    }

    if(fgets(buffer, sizeof(buffer), fptr) != NULL) {
        if(sscanf(buffer, "%d,%d", &e, &n) == 2) {
            printf("e: %d\n", e);
            printf("n: %d\n", n);
        } else {
            fprintf(stderr, "Error parsing values\n");
            fclose(fptr);
            return;
        }
    } else {
        fprintf(stderr, "Error reading file\n");
        fclose(fptr);
        return;
    }
    fclose(fptr);
    return;
}