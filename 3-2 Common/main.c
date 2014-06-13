#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
double f1 (double x){
    return x * cos(x) - sin(x * x);
}
 
double integr(double (*f) (double), double a, double b, int n, double e, int m) {
 
    double h,  xi, temp, s, ans;
    int i, k = 0;
 
    h = (b - a) / n;
    temp = a;
    ans = 0;
    for (i = 1; i <= n; ++i){
        xi = a + i * h;
        ans += (h / 2.0) * (f(temp) + f(xi));
        temp = xi;
    }
    do {
        s = ans;
        n *= 2;
        h = (b - a) / n;
        temp = a;
        ans = 0;
        for (i = 1; i <= n; ++i){
            xi = a + i * h;
            ans += (h / 2.0) * (f(temp) + f(xi));
            temp = xi;
        }
        ++ k;
    } while ((k <= m) && (fabs(ans - s) > e));
    printf (": %i\n", k - 1);
 
    return ans;
}
 
int main (){
    printf ("zzz\n");
    printf("int = %f\n", integr(&f1, -1, 1, 5, 1.e-12, 20));
    printf ("!!!\n");
}