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
    
    for(int i = 0; i < 32; ++i) {
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
    
    // You can replace "program.c" with any text file containing C code
    // For lab, we often just read direct input or a dummy file.
    // Here we will simulate reading a simple input string for demonstration.
    // In actual lab, use: fp = fopen("program.c","r");
    
    printf("Enter the C code string (end with $): ");
    
    while((ch = getchar()) != '$') {
        
        // Check for Operators
        for(i = 0; i < 10; ++i) {
            if(ch == operators[i])
                printf("%c is operator\n", ch);
        }
        
        // Check for Alphanumeric (Keywords or Identifiers)
        if(isalnum(ch)) {
            buffer[j++] = ch;
        } else if((ch == ' ' || ch == '\n' || strchr(operators, ch)) && (j != 0)) {
            buffer[j] = '\0';
            j = 0;
            
            if(isKeyword(buffer) == 1)
                printf("%s is keyword\n", buffer);
            else {
                // Check if it is a number (Constant) or Identifier
                if(isdigit(buffer[0]))
                    printf("%s is constant\n", buffer);
                else
                    printf("%s is identifier\n", buffer);
            }
        }
    }
    return 0;
}
