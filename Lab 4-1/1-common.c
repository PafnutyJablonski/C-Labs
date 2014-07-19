#include <stdio.h>
#include <string.h>
#include<float.h>

int find_row(double **A, int n, int i){
    int j = i;
    while((j < n)&&(A[j][i] == 0)){
        ++j;
    }
    return j;
};

int main(void){
    int i, j, k, l;
    double m, s, tmp;
    unsigned n;
    double* t;
    scanf("%u", &n);
    double **A = (double**)malloc(n*sizeof(double*));
    double **B = (double**)malloc(n*sizeof(double*));
    double *R = (double**)malloc(n*sizeof(double*));
    double *f = (double*)malloc(n * sizeof(double));
    double *f1 = (double*)malloc(n * sizeof(double));
    double *x = (double*)malloc(n * sizeof(double));
    for(i = 0; i < n; ++i){
        A[i] = (double*)malloc(n * sizeof(double));
    }
    for(i = 0; i < n; ++i){
        B[i] = (double*)malloc(n * sizeof(double));
    }
    for(i = 0; i < n; ++i){
            for(j = 0; j < n; ++j){
                scanf("%lf", &A[i][j]);
                B[i][j] = A[i][j];
            }
            scanf("%lf", &f[i]);
            f1[i] = f[i];
    };
    for(i = 0; i < n; ++i){
        if((l = find_row(A, n, i)) >= n){
            return 1;
        }
        t = A[l];
        A[l] = A[i];
        A[i] = t;
        tmp = f[l];
        f[l] = f[i];
        f[i] = tmp;
        for(j = i+1; j < n; ++j){
            m = A[j][i] / A[i][i];
            for(k = i; k < n; ++k){
                A[j][k] = A[j][k] - m * A[i][k];
            }
            f[j] = f[j] - m*f[i];
        }
    };
    for(i = 0; i < n; ++i){
            for(j = 0; j < n; ++j){
                printf("%.1lf    ", A[i][j]);
            }
            printf("%.1lf    \n", f[i]);
    };
    x[n-1] = f[n-1] / A[n-1][n-1];
    for(i = n-1; i >= 0; --i){
        s = 0;
        for(j = i+1; j < n; ++j){
            s += A[i][j] * x[j];
        }
        for(k = n; k > 0; --k){
            x[i] = (f[i] - s)/ A[i][i];
        }
    }
    for(i = 0; i < n; ++i){
        R[i] = 0;
        for(j = 0; j < n; ++j){
            R[i] += B[i][j] * x[j];
        }
        R[i] -= f1[i];
    }
    printf("Answer    Residual\n");
    for(i = 0; i < n; ++i){
        printf("%e    %e\n", x[i], R[i]);
    }
    return 0;
};
