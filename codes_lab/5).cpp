#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char input[100];
int i = 0;

// Function Prototypes
void E();
void Ed();
void T();
void Td();
void F();

void error() {
    printf("\nError in parsing string!\n");
    exit(0);
}

int main() {
    printf("Recursive Descent Parser for Arithmetic Expression\n");
    printf("Grammar:\n");
    printf("E -> TE'\nE' -> +TE' | epsilon\nT -> FT'\nT' -> *FT' | epsilon\nF -> (E) | i\n");
    printf("Enter the input string (use 'i' for identifier, e.g., i+i*i): ");
    scanf("%s", input);

    E(); // Start Parsing from Start Symbol

    // If parsing finished and we reached end of string
    if (strlen(input) == i) {
        printf("\nString Accepted\n");
    } else {
        printf("\nString Rejected\n");
    }
    return 0;
}

// E -> T E'
void E() {
    T();
    Ed();
}

// E' -> + T E' | epsilon
void Ed() {
    if (input[i] == '+') {
        i++;
        T();
        Ed();
    }
}

// T -> F T'
void T() {
    F();
    Td();
}

// T' -> * F T' | epsilon
void Td() {
    if (input[i] == '*') {
        i++;
        F();
        Td();
    }
}

// F -> ( E ) | i
void F() {
    if (input[i] == '(') {
        i++;
        E();
        if (input[i] == ')') {
            i++;
        } else {
            error();
        }
    } else if (input[i] == 'i') {
        i++;
    } else {
        error();
    }
}
