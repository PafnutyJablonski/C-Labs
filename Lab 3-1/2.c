#include <stdio.h>
#include <limits.h>
typedef unsigned char NUM;

int main(void){
    NUM a, ans, j, tmp;
    int i;
    scanf("%d", &a);
    ans = 0;
    for(i = sizeof(a) * 8 - 1, j = 0; i >= 0; --i, ++j){
        tmp =  ((a >> j) & 1) << i;
        ans = ans | tmp;
    }
    printf("Result: %d", ans);
    return 0;
}
