#include <stdio.h>
#include <limits.h>


int main (void){
    unsigned int a, MAX, n, res;
    scanf("%d %d", &a, &n);
    MAX = UINT_MAX;
    res = 1;
    while(n){
        if(n % 2 == 1){
            if(MAX / res < a){
                printf("Overflow");
                return 0;
            }
            res *= a;
            --n;
        }else{
            if(MAX / a < a){
                printf("Overflow");
                return 0;
            }
            a *= a;
            n >>= 1;
        }
    }
    printf("Result: %u", res);
    return 0;
}
