#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void insecure_copy(char *input) {
    char buffer[10];
    // Vulnerable to buffer overflow if input is longer than 9 characters
    strcpy(buffer, input);
    printf("Copied input: %s\n", buffer);
}

void read_file(char *filename) {
    char command[256];
    // Unsafe use of `system()` allows command injection
    sprintf(command, "cat %s", filename);
    system(command);
}

int main(int argc, char *argv[]) {
    char *password = (char *)malloc(20);
    if (!password) {
        perror("Failed to allocate memory");
        return 1;
    }

    // Vulnerable to buffer overflow and uninitialized read
    printf("Enter password: ");
    gets(password); // Unsafe function, should use fgets instead
    if (strcmp(password, "supersecret") == 0) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }

    if (argc > 1) {
        // Insecurely handles user input to execute a command
        read_file(argv[1]);
    }

    // Missing free() for password (Memory leak)
    return 0;
}

