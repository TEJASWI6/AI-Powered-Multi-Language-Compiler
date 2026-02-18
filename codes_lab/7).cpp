#include <stdio.h>
#include <string.h>

int main() {
    char input[100], left[50], right[50], alpha[50], beta[50];
    int i, j, k, split_index = -1;

    printf("Enter the production (e.g., E->E+T|T): ");
    scanf("%s", input);

    // 1. Check if Left Recursion Exists
    // Format is A->A... so input[0] must match input[3] (after "->")
    if (input[0] == input[3]) {
        printf("\nLeft Recursion Found: %s\n", input);

        // 2. Separate Alpha and Beta
        // input: E->E+T|T
        // index: 01234567
        // alpha is part after recursive E (+T)
        // beta is part after | (T)
        
        // Find the '|' operator
        for(i = 0; i < strlen(input); i++) {
            if (input[i] == '|') {
                split_index = i;
                break;
            }
        }

        if (split_index == -1) {
            printf("Error: Input must have alternate production (| beta)\n");
            return 1;
        }

        // Extract Alpha (start from index 4 up to split_index)
        k = 0;
        for (j = 4; j < split_index; j++) {
            alpha[k++] = input[j];
        }
        alpha[k] = '\0';

        // Extract Beta (start from split_index + 1 to end)
        k = 0;
        for (j = split_index + 1; j < strlen(input); j++) {
            beta[k++] = input[j];
        }
        beta[k] = '\0';

        // 3. Print the New Grammar
        // Original: A -> A alpha | beta
        // New:      A -> beta A'
        //           A' -> alpha A' | epsilon (#)
        
        char non_terminal = input[0];
        
        printf("\nGrammar without Left Recursion:\n");
        
        // Rule 1: A -> beta A'
        printf("%c -> %s%c'\n", non_terminal, beta, non_terminal);
        
        // Rule 2: A' -> alpha A' | #
        printf("%c' -> %s%c'|#\n", non_terminal, alpha, non_terminal);
        
    } else {
        printf("\nNo Left Recursion Found in %s\n", input);
    }

    return 0;
}
