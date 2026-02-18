#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Function to check if a word is a keyword
int isKeyword(char buffer[]) {
    char keywords[32][10] = {
        "auto","break","case","char","const","continue","default",
        "do","double","else","enum","extern","float","for","goto",
        "if","int","long","register","return","short","signed",
        "sizeof","static","struct","switch","typedef","union",
        "unsigned","void","volatile","while"
    };
    int i;
    for(i = 0; i < 32; ++i) {
        if(strcmp(keywords[i], buffer) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char ch, buffer[15], operators[] = "+-*/%=,;()";
    FILE *fp;
    int i, j = 0;
    
    printf("Enter the input string (end with $): ");
    
    while((ch = getchar()) != '$') {
        
        // 1. Check for Operators
        int isOp = 0;
        for(i = 0; i < 10; ++i) {
            if(ch == operators[i]) {
                printf("'%c' is an Operator\n", ch);
                isOp = 1;
                break;
            }
        }
        if(isOp) continue;
        
        // 2. Build the Token (Alphanumeric)
        if(isalnum(ch)) {
            buffer[j++] = ch;
        } 
        // 3. Process the Token when a separator (space/newline) is found
        else if((ch == ' ' || ch == '\n') && (j != 0)) {
            buffer[j] = '\0';
            j = 0;
            
            if(isKeyword(buffer) == 1)
                printf("'%s' is a Keyword\n", buffer);
            else {
                // VALIDATION LOGIC:
                // Check if it's a Number
                if(isdigit(buffer[0])) {
                    int validNumber = 1;
                    // Check if the rest are also digits
                    for(int k=1; k<strlen(buffer); k++) {
                        if(!isdigit(buffer[k])) {
                            validNumber = 0; 
                            break;
                        }
                    }
                    if(validNumber)
                        printf("'%s' is a Constant\n", buffer);
                    else
                        printf("'%s' is INVALID (Identifier cannot start with a digit)\n", buffer);
                }
                // It must be an Identifier
                else {
                    printf("'%s' is a Valid Identifier\n", buffer);
                }
            }
        }
    }
    return 0;
}
