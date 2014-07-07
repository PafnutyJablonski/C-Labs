#include <stdio.h>
#include <limits.h>

int main(void){
    int  a0, L, N, s, m, n, mask, i, t;
    N = 3;
    int c[3] = {2, 3, 5};
    for(n = 0; n < N; ++n){
        s = c[0];
        c[0] = -c[0] * c[n];
        for(i = 1; i < n; ++i){
            t = c[i];
            c[i] = -c[n] * c[i] + s;
            s = t;}
            c[n] = s;}
    for(i = 0; i < N; ++i){
        printf("%i ", c[i]);}
    return 0;
    };
