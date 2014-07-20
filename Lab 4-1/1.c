#include <stdio.h>

int* sorted(int *S, int n){
    int *T, i, k;
    T =(int*)malloc(sizeof(int) * n);
    if(n == 1) return 1;
    i = k = 0;
    T[n - k - 1] = S[k];
    while(S[k] == S[k+1] && k < n-1){
        T[n - k - 1] = S[k];
        ++k;
    }
    if(S[k] > S[k+1]){
        for(i = k; i < n-1; ++i){
            if(S[i] < S[i+1]){
                free(T);
                return NULL;
            }
            T[n - i - 2] = S[i+1];
        }
        S = T;
        T = NULL;
        return S;
    }else{
        for(i = k; i < n-1; ++i)
            if(S[i] > S[i+1]){
                free(T);
                return NULL;
            }
        free(T);
        return S;
    }
    free(T);
    return S;
}

int main(void){
    int *A, *B, *C, asort, bsort, i, j, k, m, n;
    m = 5;
    n = 6;
    A = (int*)malloc(sizeof(int) * m);
    B = (int*)malloc(sizeof(int) * n);
    printf("Enter %d numbers:\n", m);
    for(i = 0; i < m; ++i)
        scanf("%i", &A[i]);
    printf("Enter %d numbers:\n", n);
    for(i = 0; i < n; ++i)
        scanf("%i", &B[i]);
    A = sorted(A, m);
    B = sorted(B, n);
    i = j = k = 0;
    if(A && B){
        C = (int*)malloc(sizeof(int) * (m + n));

            while(i < m && j < n){
                if (A[i] <= B[j]){
                  C[k] = A[i];
                  ++i;
            }else{
                  C[k] = B[j];
                  ++j;
            }
            ++k;
            }
            if(i < m){
                while(i < m){
                    C[k] = A[i];
                    ++k;
                    ++i;
                }
            }else{
                while(j < n){
                    C[k] = B[j];
                    ++k;
                    ++j;
                }
            }


    }
    if(A && B){
        for(i = 0; i < (m + n); ++i)
            printf("%i ", C[i]);
    }else{
        printf("Not sorted");
    }
    return 0;
}
