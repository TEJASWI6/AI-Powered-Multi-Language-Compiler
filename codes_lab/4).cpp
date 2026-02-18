#include <stdio.h>
#include <string.h>

char input[100];
int i = 0; // Input pointer

// Function Prototypes
int S();
int A();

int main() {
    printf("Grammar is: \nS -> cAd \nA -> ab | a \n");
    printf("Enter the string: ");
    scanf("%s", input);

    // Call the Start Symbol S
    if (S() == 1 && i == strlen(input)) {
        printf("\nString is Accepted\n");
    } else {
        printf("\nString is Rejected\n");
    }
    return 0;
}

// Function for Non-Terminal S -> cAd
int S() {
    // Save current pointer for backtracking (though S has only 1 rule here)
    int save = i;
    
    // Attempt: S -> cAd
    if (input[i] == 'c') {
        i++;
        if (A()) { // Call A
            if (input[i] == 'd') {
                i++;
                return 1; // Success
            }
        }
    }
    
    // Backtrack if failed
    i = save;
    return 0;
}

// Function for Non-Terminal A -> ab | a
int A() {
    int save = i; // Save pointer to BACKTRACK later

    // Attempt 1: A -> ab
    if (input[i] == 'a') {
        i++;
        if (input[i] == 'b') {
            i++;
            return 1; // Success with 'ab'
        }
    }

    // FAILURE on Attempt 1 -> BACKTRACK
    // Reset pointer to where it was before we tried 'ab'
    i = save; 

    // Attempt 2: A -> a
    if (input[i] == 'a') {
        i++;
        return 1; // Success with 'a'
    }

    // Both failed
    return 0;
}
