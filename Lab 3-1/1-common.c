#include <stdio.h>

typedef struct{
    unsigned a, b;
    int c;
}t_pfrac;

t_pfrac new_pfrac(int a, int b, int c){
    int s2 = ((b < 0)?(-1):(1)) * ((c < 0)?(-1):(1));
    t_pfrac f;
    f.a = a;
    if(c == 0){
        f.c = 0;
        return f;
    }
    a += s2 * (abs(b) / abs(c));
    int s1 = (a < 0)?(-1):(1);
    b = abs(b) % abs(c);
    if(s1 * s2 > 0){
        f.a = abs(a);
        f.b = abs(b);
        f.c = abs(c) * s1;
    } else {
        if(a == 0){
            f.a = 0;
            f.b = abs(b);
            f.c = abs(c) *s2;
        }
        else {
            f.a = (abs(a) - 1);
            f.b = abs(c) - abs(b);
            f.c = abs(c) * s1;
        }
    };
    return f;
}

int correct_pfrac(t_pfrac f){
    if(f.c == 0) return 0;
    return 1;
};

void print_pfrac(t_pfrac f){
    char c = (f.c < 0)?('-'):('+');
    printf("%c%u(%u/%u)", c, f.a, f.b, abs(f.c));
};

t_pfrac pfrac_add(t_pfrac f1, t_pfrac f2){
    if(f1.c == 0) return f1;
    if(f2.c == 0) return f2;
    t_pfrac f;
    int nod1 = gcd(f1.b, f1.c);
    int nod2 = gcd(f2.b, f2.c);
    int s1, s2;
    (f1.c < 0)?(s1 = -1):(s1 = 1);
    (f2.c < 0)?(s2 = -1):(s2 = 1);
    if (s1 == s2) {
        f.a = f1.a + f2.a;
    }
    else {
            if (f1.a >= f2.a)
                f.a = f1.a - f2.a;
            else {
                f.a = f2.a - f1.a;
                s2 = s2 * (-1);
                //ѕри этом знак мен€етс€ на противоположный...
            }
    }
    f1.b = f1.b / nod1;
    f1.c = f1.c / nod1;
    f2.b = f2.b / nod2;
    f2.c = f2.c / nod2;
    f.c = nok(f1.c, f2.c) * s2;
    f.b = (f.c / f1.c) * f1.b + (f.c / f2.c) * f2.b;
    f.a +=  f.b / abs(f.c);
    f.b = f.b % abs(f.c);
    return f;
};

t_pfrac pfrac_sub(t_pfrac f1, t_pfrac f2){
    if(f1.c == 0) return f1;
    if(f2.c == 0) return f2;
    t_pfrac f;
    f2.c *= (-1);
    return pfrac_add(f1, f2);
 };

t_pfrac pfrac_mul(t_pfrac f1, t_pfrac f2){
    if(f1.c == 0) return f1;
    if(f2.c == 0) return f2;
    t_pfrac f;
    f1.b = f1.b + f1.a * abs(f1.c);
    f2.b = f2.b + f2.a * abs(f2.c);
    f.b = f1.b * f2.b;
    f.c = f1.c * f2.c;
    f.a = abs(f.b) / abs(f.c);
    f.b = abs(f.b) % abs(f.c);
    return f;
};

t_pfrac pfrac_div(t_pfrac f1, t_pfrac f2){
    if(f1.c == 0) return f1;
    if(f2.c == 0) return f2;
    int s2;
    t_pfrac f;
    (f2.c < 0)?(s2 = -1):(s2 = 1);
    f.c = f2.b * s2 + f2.a * f2.c;
    f.b = abs(f2.c) ;
    f.a = 0;
    return(pfrac_mul(f1, f));
 };

int cmp_pfrac(t_pfrac f1, t_pfrac f2){
    if(f1.c == 0) return 3;
    if(f2.c == 0) return 3;
    int s1, s2;
    (f1.c < 0)?(s1 = -1):(s1 = 1);
    (f2.c < 0)?(s2 = -1):(s2 = 1);
    f1.c = f2.c = nok(f1.c, f2.c);
    f1.b = f1.b + f1.a * abs(f1.c);
    f2.b = f2.b + f2.a * abs(f2.c);
    int f1b = s1 * (int)f1.b;
    int f2b = s2 * (int)f2.b;
    if (f1b < f2b) {return -1;}
    if (f1b == f2b) {return 0;}
    if (f1b > f2b) {return 1;}
}

int gcd(int a, int b){
    a = abs(a);
    b = abs(b);
    while(a!=0 && b!=0)
    {
       if(a >= b)
            a = a % b;
        else b = b % a;
    }
    return a + b;
};

int nok(int a, int b){
    return a * b / gcd(a, b);
};



int main(void){
    t_pfrac f1 = new_pfrac(0, -2, 3);
    t_pfrac f2 = new_pfrac(0, -5, 3);
    print_pfrac(pfrac_add(f1, f2));
    return 0;
};
