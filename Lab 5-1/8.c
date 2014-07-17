#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int a, b;
}t_solv;
int egcd(int a, int b, int *x, int *y);

int solv(int k1, int k2, int l, t_solv *m1, t_solv *m2){
    int g, mu, nu;
    g = egcd(k1, k2, &mu, &nu);
    if (l%g){
        m1->b = m2->b = 0;
        return 0;
    }
    m1->a = l / g * mu;
    m2->a = -l / g * nu;
    m1->b = k2 / g;
    m2->b = k1 / g;

    return g;
}

int egcd(int a ,int b, int *x, int *y){
    if (a < b){
        return egcd(b, a, y, x);
    }
    int q, r, d, x1, x2, y1, y2;
    if (b == 0) {
        d = a;
        *x = 1;
        *y = 0;
        return 1;
    }
    x2 = 1;
    x1 = 0;
    y2 = 0;
    y1 = 1;
    while (b > 0) {
        q = a / b;
        r = a - q * b;
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

int main(void){
    FILE *f1, *f2;
    int i, i0, i1, i2, inword = 0, j, k1, k2, l, n = 1, t, t1, t2, z;
    int *K, *L ;
    int lmin;
    t_solv *mset, *tmp;
    t_solv s1, s2, u1, u2;

    // Read from file
    if((f1 = fopen("input.txt", "rt")) == NULL){
        printf("cant open file");
        return 0;
    }
    while(!feof(f1)){
        if(fgetc(f1) == '\n')
            ++n;
    }
    if((K = (int*)malloc(n * sizeof(int))) == NULL){
        printf("cant allocate memory");
        return 0;
    }
    memset (K, 0, sizeof(int) * n);
    if((L = (int*)malloc(n * sizeof(int))) == NULL){
        printf("cant allocate memory");
        return 0;
    }
    memset (L, 0, sizeof(int) * n);
    if((mset = (t_solv*)malloc(n * sizeof(t_solv))) == NULL){
        printf("cant allocate memory");
        return 0;
    }
    if((tmp = (t_solv*)malloc(n * sizeof(t_solv))) == NULL){
        printf("cant allocate memory");
        return 0;
    }
    i = 0;
    fseek(f1, 0, SEEK_SET);
    do switch(fgetc(f1)) {
        case '\n':
            if (inword) {
                inword = 0;
                ++K[i];
            }
            ++i;
            break;
        case ' ':
            if (inword) {
                inword = 0;
                ++(K[i]);
            }
            break;
        case EOF:
            if (inword) {
                inword = 0;
                ++K[i];
            }
            ++i;
            break;
        default:
            inword = 1;
            ++(L[i]);
    } while(!feof(f1));

    // Find minlength of a string
    lmin = 0;
    for(i = 0; i < n; ++i){
        lmin = (lmin < L[i])?(L[i]):(lmin);
    }

    i1 = 0;
    while((i1 < n) && (K[i1] < 2)){
        ++i1;
    }
    i2 = i1 + 1;
    while((i2 < n) && (K[i2] < 2)){
        ++i2;
    }
    if(i1 >= n){
        printf("...\n");
        return 0;
    }
    if(i2 >= n){
        printf("...\n");
        return 0;
    }

    if(!(solv(K[i1]-1, K[i2]-1, L[i2] - L[i1], &(mset[i1]), &(mset[i2])))) {
        printf("no solution \n");
        return 0;
    }
    i0 = i1;
    i1 = i2;
    ++i2;
    while((i2 < n) && (K[i2] < 2)){
        ++i2;
    }

    while(i2 < n){
        if(!(solv(K[i1]-1, K[i2]-1, L[i2] - L[i1], &s1, &s2))){
            printf(" no solution \n");
        return 0;
        }
        if(!(solv(mset[i1].b, s1.b, s1.a - mset[i1].a, &u1, &u2))){
            printf(" no solution \n");
        return 0;
        }
        z = - (s1.a + u2.a * s1.b) / (u2.b * s1.b);
        u1.a = z * u1.b + u1.a;
        u2.a = z * u2.b + u2.a;
        s2.a += u2.a * s2.b;
        s2.b *= u2.b;
        s1.a += u2.a * s1.b;
        s1.b *= u2.b;
        mset[i1] = s1;
        mset[i2] = s2;
        tmp[i1].a = u1.a;
        tmp[i1].b = u1.b;
        /*for(j = i1-1; j >= 0; --j){
            if(K[j] < 2) continue;
            mset[j].a += u1.a * mset[j].b;
            mset[j].b *= u1.b;
        }*/
        i1 = i2;
        ++i2;
        while((i2 < n) && (K[i2] < 2)){
            ++i2;
        }
    }

    int q = 1, p = 0;
    for(i = i1 - 1; i >= 0; --i){
        if (K[i] < 2) {
            continue;
        }
        mset[i].a += p * mset[i].b;
        mset[i].b *= q;
        p = tmp[i].a + p * tmp[i].b;
        q = q * tmp[i].b;
        i2 = i1;
    }


    /*for(i = 0; i < n; ++i){
        printf("%i: %i %i\n", i, mset[i].a, mset[i].b);
    }*/

    for(i = 0; i < n; ++i){
        if(K[i] < 2) continue;
        t1 = - mset[i].a / mset[i].b;
        while(mset[i].a + t1 * mset[i].b > 0){
            --t1;
        }
        while(mset[i].a + t1 * mset[i].b <= 0){
            ++t1;
        }
        t2 = ((lmin - L[i]) / (K[i]-1) - mset[i].a) / mset[i].b;
        while(L[i] + (mset[i].a + t2 * mset[i].b) * (K[i]-1) > lmin){
            --t2;
        }
        while(L[i] + (mset[i].a + t2 * mset[i].b) * (K[i]-1) < lmin){
            ++t2;
        }
        t1 = (t1 > t2)?(t1):(t2);
        if (i == i0) {
            t = t1;
        }
        else {
            t = (t < t1)?(t1):(t);
        }
    }

    // Write output
    if((f2 = fopen("output.txt", "wt")) == NULL){
        printf("cant open file");
        return 0;
    }
    fseek(f1, 0, SEEK_SET);
    i = i0 = inword = 0;
    do switch(l = fgetc(f1)) {
        case '\n':
            ++i;
            fputc('\n', f2);
            inword = 0;
            i0 = 0;
            break;
        case ' ':
            if (inword) {
                inword = 0;
                ++i0;
                if(K[i] > i0){
                for(j = 0; j < (mset[i].a + t * mset[i].b); ++j){
                    fputc(' ', f2);
                    }
                }
            }
            break;
        case EOF:
            break;
        default:
            inword = 1;
            fputc(l , f2);
    } while(!feof(f1));
    fclose(f1);
    fclose(f2);
    return 0;
};



/*
K[i] - ���-�� ���� � �-������
L[i] - ��������� ������ ���� ������
M[i] - ���������� �������� ����� 2�� ������ ������� - �����, > 0,  L[i] + M[i](K[i] - 1) >= L[min]; L[min] = max[i]{L[i]};
 ����� ������ ������ ������ L[min]; �����. ���.
L[i] + M[i](K[i] - 1) = const - ����� ������; ����� ������ ������
M[i](K[i] - 1) - M[i+1](K[i+1] - 1) = L[i+1] - L[i] - ������������ ����� � - ������ � ������ �+1 - ������

kappa[i] = K[i]-1;
lambda[i] = L[i+1] - L[i];

kappa[i] * M[i] - kappa[i+1] * M[i +1] = lambda[i];
M[i+1] =  (kappa[i] * M[i] - lambda[i]) / kappa[i+1];

i : kappa[i] * M[i] - kappa[i+1] * M[i +1] = lambda[i]; ��� ������� �-�� ��������� ������� ��-�� ������� M[i] � M[i+1];
g = GCD(kappa[i], kappa[i+1]) => kappa[i] = x*g, kappa[i+1] = y*g;
x[i]*g*M[i] -y[i]*gM[i+1] = lambda[i];
(x[i]*M[i] - y[i]*M[i+1] = lambda[i] ~ gamma[i]*g, gamma[i] = lambda[i]/g; -���� ������ �� ������� ��, �� ������� �� ����� �������
g(x * M[i] y * M[i+1]) =lambda = gamma[i] * g;

x*kappa[i] + y*kappa[i+1] = g
gamma[i]*x*kappa[i] + gamma[i]*y*kappa[i+1] = gamma[i]*g;

kappa[i] = K[i] - 1;
lambda[i] = L[i+1] - L[i];
x*kappa[i] + y*kappa[i+1] = g =>  x*gamma[i]*kappa[i] + y*gamma[i]*kappa[i+1] = gamma[i] * g;
M[i] = gamma[i] * x;
M[i+1] = - gamma[i] * y;
M[i](t) = gamma[i] * x + (kappa[i+1] / g) * t;
           A[i]        +     t*B[i]
M[i+1](t) = - gamma[i] * y + (kappa[i] / g) * t ; // t -integer
                C[i]       +   t*D[i]; t [ Z;
kappa[i]*(M[i] + (kappa[i+1]/g)*t) - kappa[i+1]*(M[i+1] + (kappa[i]/g)*t) = lambda;

t1[i] = min{t: M[i](t) > 0}
t2[i] = min{t: L[i] + M[i]*(K[i] - 1) >= L[min]}
t[i] = max{t1[i], t2[i]}
t[min] = max{t[i]}
M[i](t[min]) - ������� �����

t[l] = t[0] + S[i] * l;
tau[l] = tau[0] + sigma[i] * l;
Mi[i+1](t[l]) = (C[i] + t[0] * D[i]) +l * S[i] * D[i];
Mi+1[i+1](tau[l]) = (A[i+1] + tau[0] * B[i+1]) + l * G[i] * B[i+1];
(t[l], tau[l]): Mi[i+1](t[l]) = Mi+1[i+1](tau[l]);
C[i] +t * D[i] = A[i+1] + tau * B[i+1];
t * D[i] - tau * B[i+1] = A[i+1] - C[i];
M[i] = Mi[i+1] ����������� Mi+1[i+1] = M[i+1](t[l]) = (C[i] + t[0] * D[i]) +l * S[i] * D[i] - ������������� ����������� �������� �� l

Algo:
1) kappa[1] * M[1] - kappa[2] * M[2] = lambda[1];
    M1[1]{t) = A[1] + t * B[1]
    M1[2](t) = C[1] + t * D[1]; - ������ ���-�� �1 � �2 ��������������� ���������
2) for(i = 2; i < n)
    kappa[i] * M[i] - kappa[i+1] * M[i+1] = lambda[i];
        Mi[i](t) = A[i] + t * B[i]
        Mi[i+1](t) = C[i] + t * D[i]
   M[i] = Mi-1[i] ����������� Mi[i] - ����� �����������
   (t[l], tau[l]): Mi-1[i](tau[l]) = Mi[i](t[l]) => tau * B[i] - t * D[i-1] = A[i] - C[i-1];
        t[l] = t[0] + l * S
        tau[l] = tau[0] + l * sigma
   M[i](l) = Mi-1[i](t[l]) = (C[i-1] + t[0] * D[i-1]) + l * S * D[i-1]
             Mi[i](tau[l]) = (A[i] + tau[0] * B[i]) + l * sigma * B[i]
   M[i+1] = Mi[i+1](tau[l]) = (C[i] + tau[0] * D[i]) l * sigma D[i] - �������� ����������� ��������
   for(j = 1; j < i)
       M[j](l) = M[j](t[l]) = (A[j] + t[0] * B[j]) + j * S * B[j]
3) for(i = 1; i <= n)
       t1[i] min{t: M[i](t) > 0}, t2[i] = min{t: L[i] + M[i](t) * (K[i] -1) >= L[min]}
       t[i] = max{t1[i], t2[i]}
4) t[min] = max{t[i]}, M[i](t[min])

A[i] - ��������
B[i] - ��� ���������

M[1](t) = A[1] + t * B[1] => M[1](l) = (A[1] + t[0] * B[1]) + l * S[2] * B[1]
M[2](t) = C[1] + t * D[1]
M`[j](l) = ( A[1] + for(j= i+1; j < n){+= t0[j]}(for(k = i+1; k <= j){*= S[k]}) * B[i]) => A`[i] = A[i] + P[i] * B[i]
B`[i] = (for(j = i+1; j < n){*= S[j]}) * B[i] => B`[i] = Q[i] * B[i]
Q[i] = S[i+1] * Q[i+1]

<time.h>
clock();

*/
