#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// entrada 1: (7(5()(6))(10()(12)))
// entrada 2: (12(5()(6))(10()(1)))

void return_brackets(char* s, char v[]){
    char *bracket;
    int i = 0, j = 0;

    bracket = strchr(s, '(');
    while(s[i] != '\0'){
        if(*(bracket+i) == '(' || *(bracket+i) == ')'){
            v[j] = *(bracket+i);
            j++;
        }
        i++;
    }
}

int quant_alfa(char *s){
    int i = 0;
    int cont = 0;
    while(s[i] != '\0'){
        if(s[i] == '(' || s[i] == ')'){
            cont++;
        }
        i++;
    }
    return cont;
}


int main(){
    char *pt, line[] = "(12(5()(6))(10()(1)))";
    int i = 0, cont = 0;
    pt = strtok(line, "()");
    while(pt){
        if(isalnum(*(pt))){
            cont++;
        }
        pt = strtok(NULL, "()");
        i++;
    }
    printf("cont = %i", i);
    int alfa = quant_alfa(line);
    printf("\nalfa = %d", alfa);
    return 0;
}
