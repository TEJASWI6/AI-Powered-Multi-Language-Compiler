%{
#include<stdio.h>
%}

%%
[0-9]+      { printf("Number\n"); }
[a-zA-Z]+   { printf("Identifier\n"); }
"+"|"-"|"*"|"/" { printf("Operator\n"); }
[ \t\n]     ;
.           { printf("Special Character\n"); }
%%

int main() {
    yylex();
    return 0;
}

