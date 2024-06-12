#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//extern void encrypt(unsigned int d, unsigned int n);
//extern void decrypt(unsigned int e, unsigned int n);
extern void generateKeys();

unsigned int modular_exponentation(unsigned int a, unsigned int b, unsigned int m);
char* encrypt();

int modInverse(int A, int M) {
    for (int X = 1; X < M; X++) {
        int aMod = A % M;
        int xMod = X % M;
        int axMod = aMod * xMod;
        int mod = axMod % M;
        if (mod == 1) {
            return X;
        }
    }
    return -1;
}

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
            printf("d: %d\n", d);
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

int reverse_number(int num) {
    char str[20];
    char temp;
    int len, i;
    
    snprintf(str, sizeof(str), "%d", num);
    
    len = strlen(str);
    
    for (i = 0; i < len / 2; i += 2) {
        temp = str[i];
        str[i] = str[len - i - 2];
        str[len - i - 2] = temp;
        
        temp = str[i + 1];
        str[i + 1] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    
    return atoi(str);
}

char* encrypt() {
    FILE *fptr;
    char buffer[100];
    int e,n;

    fptr = fopen("key_pub.txt", "r");
    if (fptr == NULL) {
        printf("Couldn't write public key file.");
        return NULL;
    }

    if(fgets(buffer, sizeof(buffer), fptr) != NULL) {
        if(sscanf(buffer, "%d,%d", &e, &n) == 2) {
            
        } else {
            fprintf(stderr, "Error parsing values\n");
            fclose(fptr);
            return NULL;
        }
    } else {
        fprintf(stderr, "Error reading file\n");
        fclose(fptr);
        return NULL;
    }
    fclose(fptr);

    char input[100];
    int output[10];
    for(int i = 0; i < 10; i++) {
        output[i] = 0;
    }
    int outputIterator = 0;
    printf("Podaj tekst do zaszyfrowania (tylko cyfry i litery): ");
    scanf("%s", input);
    int exponent = 0;
    int number = 0;
    int i = 0;
    for(; i < 100; i++) {
        char letter = input[i];
        if (letter == '\0') {
            break;   
        }
        if(letter < ' ' || letter > 'z') {
            printf("Nieprawidłowe dane wejściowe!\n");
            return NULL;
        }
        
        int asciiValue = ((int) letter) - 22;
        int buffer_number = number;
        buffer_number += pow(10, exponent) * asciiValue;
        buffer_number = reverse_number(buffer_number);
        if(buffer_number > n) {
            output[outputIterator++] = reverse_number(number);
            number = 0;
            i--;
            exponent = 0;
            continue;
        }
        number = reverse_number(buffer_number);
        exponent += 2;
        if (input[i + 1] == '\0') {
            output[outputIterator++] = reverse_number(number);
        }
    }

    printf("e: %d, n: %d\n", e, n);
    char finalOutput[outputIterator][5];
    int finalOutuptInterator = 0;
    int maxLength = -1;
    for(int i = 0; i < outputIterator; i++) {
        char encrypted[5];
        printf("Not decrypted data before: %d\n", output[i]);
        int modExpression = modular_exponentation(output[i], e, n);
        printf("Decrypted data before: %d\n", modExpression);
        sprintf(encrypted, "%d", modExpression);
        int strLen = strlen(encrypted);
        if(strLen < 5) {
            char fixed[5];
            for(int i = 0; i < 5 - strLen; i++) {
                fixed[i] = '0';
            }
            int j = 0;
            for(int i = 5 - strLen; i < 5; i++) {
                fixed[i] = encrypted[j];
                j++;
            }
            
            for(int i = 0; i < 5; i++) {
                encrypted[i] = fixed[i];
            }
        }
        for(int i = 0; i < 5; i++) {
            finalOutput[finalOutuptInterator][i] = encrypted[i];
        }
        finalOutuptInterator++;
    }
    int finalLength = outputIterator * 5;
    char *finalFinalOutput = (char*)malloc(finalLength * sizeof(char)); 
    int iterator = 0;
    for(int i = 0; i < outputIterator; i++) {
        for(int j = 0; j < 5; j++) {
            finalFinalOutput[iterator++] = finalOutput[i][j];
        }
    }
    printf("%s\n", finalFinalOutput);
    return finalFinalOutput;
}

unsigned int modular_exponentation(unsigned int a, unsigned int b, unsigned int m) {
    unsigned int result = 1;
    a = a % m;
    if (a == 0) {
        return 0;
    }
    while (b > 0) {
        if((b & 1) == 1) {
            result = (result * a) % m;
        }
        b = b >> 1;
        a = (a * a) % m;
    }
    return result;
}

void decrypt(char* c) {
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
            printf("d: %d\n", d);
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

    int cLength = strlen(c);
    char result[cLength];
    int partNumber = cLength / 5;
    char messageParts[partNumber][6]; 
    for(int i = 0; i < partNumber; i++) {
        for(int j = 0; j < 5; j++) {
            messageParts[i][j] = c[j + (i * 5)];
        }
        messageParts[i][6] = '\0';
    }
    for(int i = 0; i < partNumber; i++) {
        printf("Decrypted data after: %d\n", atoi(messageParts[i]));
        int number = modular_exponentation(atoi(messageParts[i]), d, n);
        printf("Not decrypted data after: %d\n", number);
        int a = number % 100 + 22;
        int b = (number - a - 22) / 100 + 22; 

        //printf("number2: %d, %d-%d\n", number, a, b);
    }
}

void main(int argc, char *argv[]) {
    generateKeys();
    char* encryptedMessage = encrypt();
    decrypt(encryptedMessage);
}
