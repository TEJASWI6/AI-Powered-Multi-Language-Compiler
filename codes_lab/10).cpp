#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char stack[50], input[50], action[50];
int top = -1;

// Push to Stack
void push(char c) {
    stack[++top] = c;
    stack[top + 1] = '\0';
}

// Pop from Stack
void pop() {
    top--;
    stack[top + 1] = '\0';
}

// Function to print stack and input
void print_status() {
    printf("$%s\t\t%s$\t\t%s\n", stack, input, action);
}

// Check if we can REDUCE
void check() {
    // 1. Check for handle 'i' -> Reduce to E
    if (stack[top] == 'i') {
        pop();
        push('E');
        strcpy(action, "Reduce E->i");
        print_status();
        check(); // Recursively check if new stack can be reduced further
    }
    // 2. Check for handle 'E+E' -> Reduce to E
    else if (top >= 2 && stack[top] == 'E' && stack[top-1] == '+' && stack[top-2] == 'E') {
        pop(); pop(); pop();
        push('E');
        strcpy(action, "Reduce E->E+E");
        print_status();
        check();
    }
    // 3. Check for handle 'E*E' -> Reduce to E
    else if (top >= 2 && stack[top] == 'E' && stack[top-1] == '*' && stack[top-2] == 'E') {
        pop(); pop(); pop();
        push('E');
        strcpy(action, "Reduce E->E*E");
        print_status();
        check();
    }
    // 4. Check for handle '(E)' -> Reduce to E
    else if (top >= 2 && stack[top] == ')' && stack[top-1] == 'E' && stack[top-2] == '(') {
        pop(); pop(); pop();
        push('E');
        strcpy(action, "Reduce E->(E)");
        print_status();
        check();
    }
}

int main() {
    printf("Shift Reduce Parser for Grammar: E->E+E | E*E | (E) | i\n");
    printf("Enter the input string (e.g., i+i*i): ");
    scanf("%s", input);
    
    printf("\nStack\t\tInput\t\tAction\n");
    printf("------------------------------------------------\n");
    
    int len = strlen(input);
    
    // Initial State
    strcpy(action, "Start");
    
    // Loop through input
    for (int i = 0; i < len; i++) {
        // SHIFT
        char ch = input[i];
        
        // Remove processed char from input string for display purposes
        // (Just shift the pointer logic or print substring)
        // Here we just modify input array directly to show it "shrinking"
        // But for this simple code, we just shift onto stack.
        
        push(ch);
        input[i] = ' '; // Mark as used (visual only)
        
        strcpy(action, "Shift");
        print_status();
        
        // CHECK REDUCE
        check();
    }
    
    // Final Check
    if (top == 0 && stack[top] == 'E') {
        printf("\nString Accepted\n");
    } else {
        printf("\nString Rejected\n");
    }
    return 0;
}
