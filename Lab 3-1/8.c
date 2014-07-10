#include <stdio.h>

long egcd(unsigned a, unsigned b, long *x, long *y)
{
     long  d, x1, x2, y1, y2;
     if(a < b){
        return egcd(b, a, &x, &y);
     }
     if (b == 0){
        d = a;
        x = 1;
        y = 0;
        return d;
     }
     x2 = 1;
     x1 = 0;
     y2 = 0;
     y1 = 1;
     while(b > 0){
        int q = a / b;
        int r = a - q * b;
        *x = x2 - q * x1;
        *y = y2 - q * y1;
        a = b;
        b = r;
        x2 = x1;
        x1 = *x;
        y2 = y1;
        y1 = *y;
     }
     d = a;
     *x = x2;
     *y = y2;
     return d;
}

int main(void)
{

    long a = 20, b = 15, d, i, k, x, y;
    d = egcd(a, b, &x, &y);
    printf("x = %ld y = %ld d = %ld\n", x, y, d);
    k = -x / (b / d);
    while( x + k * (b / d) > 0){
        --k;
   }
    while(x + k * (b/d) <= 0){
        ++k;
    }
    for(i = k -1; i < k + 5; ++i)
        printf("(%ld, %ld) %ld\n", x + i * (b / d), y - i * (a / d), (x + i * (b / d)) * a + (y - i * (a / d)) * b - d);
    return 0;
}
