#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char line[] = "(7(5()(6))(10()(12)))";
    int len = strlen(line);
    char *pt;
    int v[10];
    char v1[len][len];
    int i = 0;

    pt = strtok(line, "()");
    while(pt){
        v[i] = atoi(pt);
        pt = strtok(NULL, "()");
        i++;
    }

    for(int i = 0; i<5; i++){
        printf("num %i: %i\n", i, v[i]);
    }

    return 0;
}