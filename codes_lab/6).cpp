#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int n, m = 0, p, i = 0, j = 0;
char a[10][10], f[10];

// Function Prototypes
void follow(char c);
void first(char c);

int main() {
    int i, z;
    char c, ch;
    
    printf("Enter the no of productions:\n");
    scanf("%d", &n);
    
    printf("Enter the productions:\n");
    for(i=0; i<n; i++)
        scanf("%s%c", a[i], &ch); // Reads string like "S=Ab"
        
    do {
        m = 0;
        printf("Enter the elemets for whose first & follow is to be found:");
        scanf("%c", &c);
        
        // --- COMPUTE FIRST ---
        first(c);
        printf("First(%c) = { ", c);
        for(i=0; i<m; i++)
            printf("%c ", f[i]);
        printf("}\n");
        
        // --- COMPUTE FOLLOW ---
        strcpy(f, " ");
        m = 0; // Reset result array index
        follow(c);
        printf("Follow(%c) = { ", c);
        for(i=0; i<m; i++)
            printf("%c ", f[i]);
        printf("}\n");
        
        printf("Continue(0/1)?");
        scanf("%d%c", &z, &ch);
    } while(z == 1);
    
    return 0;
}

// Function to calculate First
void first(char c) {
    int k;
    if(!isupper(c)) { // If it is a terminal
        f[m++] = c;
    }
    for(k=0; k<n; k++) {
        if(a[k][0] == c) { // Find productions starting with 'c'
            if(a[k][2] == '#') { // If X -> epsilon
                follow(a[k][0]); // Epsilon logic often handled differently, but in simple First:
                f[m++] = '#'; 
            } else if(islower(a[k][2])) { // If X -> a... (terminal)
                f[m++] = a[k][2];
            } else { // If X -> Y... (non-terminal)
                first(a[k][2]);
            }
        }
    }
}

// Function to calculate Follow
void follow(char c) {
    if(a[0][0] == c) // If Start Symbol, add $
        f[m++] = '$';
        
    for(i=0; i<n; i++) {
        for(j=2; j<strlen(a[i]); j++) {
            if(a[i][j] == c) {
                if(a[i][j+1] != '\0') { // If something follows 'c'
                    first(a[i][j+1]);
                }
                if(a[i][j+1] == '\0' && c != a[i][0]) { // If 'c' is at end
                    follow(a[i][0]); // Follow(LHS)
                }
            }
        }
    }
}
