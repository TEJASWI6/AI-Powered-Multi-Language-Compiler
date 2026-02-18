#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Global Arrays
char stack[50];
int top = -1;
char input[50];
int i = 0;

// Grammar: E->E+E | E*E | (E) | d
// simplified to: E->d  (for extremely simple Shift Reduce test)
// OR the S->CC one. 
// Let's use the standard "Shift Reduce" logic which is generic.

void push(char c) {
    stack[++top] = c;
    stack[top+1] = '\0';
}

void pop() {
    top--;
    stack[top+1] = '\0';
}

void print_status() {
    printf("$%s\t\t%s$\t\t", stack, input+i);
}

int main() {
    // This is technically Experiment 10 (Shift Reduce Parser)
    // But often used for Exp 9 as well if specific table isn't required.
    // If your manual distinguishes them strict table vs stack logic:
    // This code implements the STACK logic for S->0S0 | 1S1 | 2
    
    printf("LR Parsing (Shift-Reduce) for Grammar: S -> 0S0 | 1S1 | 2\n");
    printf("Enter String: ");
    scanf("%s", input);
    
    int len = strlen(input);
    
    printf("\nStack\t\tInput\t\tAction\n");
    printf("----------------------------------------\n");
    
    // Shift-Reduce Logic
    for(i=0; i<len; i++) {
        // SHIFT
        push(input[i]);
        print_status();
        printf("Shift %c\n", input[i]);
        
        // REDUCE CHECK (Repeatedly)
        // Check for S -> 2
        if(stack[top] == '2') {
            pop();
            push('S');
            print_status();
            printf("Reduce S->2\n");
        }
        
        // Check for S -> 0S0 or 1S1
        if(top >= 2) {
            if(stack[top] == '0' && stack[top-1] == 'S' && stack[top-2] == '0') {
                pop(); pop(); pop();
                push('S');
                print_status();
                printf("Reduce S->0S0\n");
            }
            else if(stack[top] == '1' && stack[top-1] == 'S' && stack[top-2] == '1') {
                pop(); pop(); pop();
                push('S');
                print_status();
                printf("Reduce S->1S1\n");
            }
        }
    }
    
    if(strcmp(stack, "S") == 0) 
        printf("\nString Accepted\n");
    else 
        printf("\nString Rejected\n");
        
    return 0;
}
