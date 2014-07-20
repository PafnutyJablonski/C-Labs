#include <stdio.h>
#include <string.h>

int main(void){
    int i, j, k, len, res;
    char a, b;
    scanf("%c %c", &a, &b);
    char *s = "ababababba";
    len = strlen(s);
    j = k = res = 0;
    for(i = 0; i < len; ++i){
        if(s[i] == a){
            ++j;
        }
        if(s[i] == b){
            if(a == b) --res;
            ++k;
            res += j;
        }
    }
    printf("Reslut: %i", res);
    return 0;
}

