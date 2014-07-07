#include <stdio.h>
#include <limits.h>

#define TYPE unsigned int
#define MAX_BIT (sizeof(TYPE) * CHAR_BIT)
#define MAX_VALUE (UINT_MAX)

int main(void){
    unsigned int  a, n, s, m, mask, i, t;
    scanf("%u", &n);
    s = 0;
    mask = MAX_VALUE >> (MAX_BIT - n);
    t = (MAX_BIT / n) - (MAX_BIT%n == 0);
    a = MAX_VALUE;
    //a = 63;
    printf("%u %u \n", a, n);
    for(i=0; i <= t; ++i){
        m = a >> (MAX_BIT - n*i);
        m = m & (mask);
        s += m;
    };
    printf("%u", s);
    return 0;
}
