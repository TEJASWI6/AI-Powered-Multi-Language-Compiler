#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char stack[20], input[20];
int top = -1, i = 0;

// Stack Operations
void push(char c) {
    stack[++top] = c;
}

void pop() {
    top--;
}

void print_stack() {
    for (int j = 0; j <= top; j++)
        printf("%c", stack[j]);
    printf("\t\t");
}

void print_input() {
    for (int j = i; j < strlen(input); j++)
        printf("%c", input[j]);
    printf("\n");
}

// FIX: Define error() BEFORE main()
void error() {
    printf("\nError: Invalid String\n");
    exit(0);
}

int main() {
    printf("Predictive Parser for Grammar:\n");
    printf("E->TE' | E'->+TE'|# | T->FT' | T'->*FT'|# | F->(E)|i\n");
    printf("Enter input string (append $): ");
    scanf("%s", input); 

    // Initialize Stack with Start Symbol 'E' and '$'
    push('$');
    push('E');

    printf("\nStack\t\tInput\n");
    printf("-----------------------------\n");

    while (top != -1) {
        print_stack();
        print_input();
        
        char x = stack[top];
        char a = input[i];

        // Case 1: Stack top is Terminal
        if (x == a) {
            if (x == '$') {
                printf("\nString Accepted!\n");
                break;
            }
            pop();
            i++;
        }
        // Case 2: Stack top is Terminal but doesn't match Input
        else if (x == '+' || x == '*' || x == '(' || x == ')' || x == 'i') {
            printf("\nError: Mismatch Terminal\n");
            break;
        }
        // Case 3: Stack top is Non-Terminal (Expand using Table)
        else {
            pop(); // Pop Non-Terminal
            
            // E -> TE'
            if (x == 'E') {
                if (a == 'i' || a == '(') {
                    push('Z'); // Z represents E'
                    push('T');
                } else error();
            }
            // E' -> +TE' | #
            else if (x == 'Z') { // Z is E'
                if (a == '+') {
                    push('Z');
                    push('T');
                    push('+');
                } else if (a == ')' || a == '$') {
                    // Epsilon: Do nothing (just popped Z)
                } else error();
            }
            // T -> FT'
            else if (x == 'T') {
                if (a == 'i' || a == '(') {
                    push('Y'); // Y represents T'
                    push('F');
                } else error();
            }
            // T' -> *FT' | #
            else if (x == 'Y') { // Y is T'
                if (a == '*') {
                    push('Y');
                    push('F');
                    push('*');
                } else if (a == '+' || a == ')' || a == '$') {
                    // Epsilon
                } else error();
            }
            // F -> (E) | i
            else if (x == 'F') {
                if (a == '(') {
                    push(')');
                    push('E');
                    push('(');
                } else if (a == 'i') {
                    push('i');
                } else error();
            }
        }
    }
    return 0;
}
