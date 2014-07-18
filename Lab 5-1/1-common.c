#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#define ALPH_SIZE (UCHAR_MAX+1)
typedef unsigned char BYTE;

int KMP(const BYTE *T, int m, FILE *s){
    int  counter = 0, i, j, k1, k, l, num;
    int *pi;
    long pos = 0;
    long start = ftell(s);
    BYTE *BUFF;
    if((pi = (int*)malloc(sizeof(int) * m)) == NULL){
        printf("Cant allocate memory");
        return 0;
    }
    if ((BUFF = (BYTE*) malloc(sizeof(BYTE) * m)) == NULL){
        printf("Cant allocate memory");
        return (-1);
    }
    num = fread(BUFF, 1, m, s);
    BYTE c;
    pi[0] = 0;
    for(i = 1; i < m; ++i){
        j = pi[i-1];
        while(j > 0 && T[i] != T[j])
            j = pi[j-1];
        if(T[i] == T[j]) ++j;
        pi[i] = j;
    }
    k1 = 0;
    while(num == m){
        for(k = k1; k < m; ++k){
            if(T[k] !=  BUFF[k])
                break;
        }
        if(k >= m){
            ++counter;
            l = m;
            k1 = 0;
        }
        else{
            k1 = pi[k];
            l = k - k1;
            l = (l == 0)?(1):(l);
            memmove(BUFF, BUFF + l, m - 1);
        }
        num = (m - l) + fread(BUFF + (m - l), 1, l, s);
    }
    fseek(s, start, SEEK_SET);
    free(BUFF);
    return counter;
}

int search_naive(const BYTE *T, int m, FILE *s){
    int  counter = 0, i, j, k, l, p = 0, num;
    long pos = 0;
    long start = ftell(s);
    BYTE *BUFF;
    if ((BUFF = (BYTE*) malloc(sizeof(BYTE) * m)) == NULL)
        return (-1);
    num = fread(BUFF, 1, m, s);
    BYTE c;
    while(num == m){
        for(k = 0; k < m; ++k){
            if(T[k] != (c = BUFF[k]))
                break;
        }
        if(k >= m){
            ++counter;
            l = m;
        }
        else {
            c = BUFF[m-1];
            l = 1;
            memmove(BUFF, BUFF + l, m - l);
        }
        num = (m - l) + fread(BUFF + (m - l), 1, l, s);
    }
    fseek(s, start, SEEK_SET);
    free(BUFF);
    return counter;
}

int search_BMH(const BYTE *T, int m, FILE *s){
    static int SHIFT[ALPH_SIZE];
    int  counter = 0, i, j, k, l, p = 0, num;
    long pos = 0;
    long start = ftell(s);
    BYTE *BUFF;
    if ((BUFF = (BYTE*) malloc(sizeof(BYTE) * m)) == NULL)
        return (-1);
    BYTE c;
    for(i = 0 ; i < ALPH_SIZE; ++i){
        SHIFT[i] = m;
    }
    for(j = m-2; j >= 0; --j){
        if(SHIFT[T[j]] == m)
            SHIFT[T[j]] = m - (j+1);
    }
    num = fread(BUFF, 1, m, s);
    while(num == m){
        for(k = 0; k < m; ++k){
            if(T[k] != (c = BUFF[k]))
                break;
        }
        if(k >= m){
            ++counter;
            l = m;
        }
        else {
            c = BUFF[m-1];
            l = SHIFT[c];
            memmove(BUFF, BUFF + l, m - l);
        }
        num = (m - l) + fread(BUFF + (m - l), 1, l, s);
    }
    fseek(s, start, SEEK_SET);
    free(BUFF);
    return counter;
}

int search_BMH2(const BYTE *T, int m, FILE *s){
    static int SHIFT[ALPH_SIZE];
    int  counter = 0, i, j, k, p = 0, num;
    long pos = 0;
    long start = ftell(s);
    BYTE *BUFF;
    if ((BUFF = (BYTE*) malloc(sizeof(BYTE) * m)) == NULL)
        return (-1);
    BYTE c;
    for(i = 0 ; i < ALPH_SIZE; ++i){
        SHIFT[i] = m;
    }
    for(j = m-2; j >= 0; --j){
        if(SHIFT[T[j]] == m)
            SHIFT[T[j]] = m - (j+1);
    }
    num = fread(BUFF, 1, m, s);
    while(num == m){
        for(k = 0; k < m; ++k){
            if(T[k] != (c = BUFF[k]))
                break;
        }
        if(k >= m){
            ++counter;
        }
        else {
            c = BUFF[m-1];
            fseek(s, SHIFT[c] - m, SEEK_CUR);
        }
        num = fread(BUFF, 1, m, s);
    }
    fseek(s, start, SEEK_SET);
    free(BUFF);
    return counter;
}

int search_BMH1(const BYTE *T, int m, FILE *s){
    static int SHIFT[ALPH_SIZE];
    int  counter = 0, i, j, k, p = 0;
    long pos = 0;
    long start = ftell(s);
    BYTE c;
    for(i = 0 ; i < ALPH_SIZE; ++i){
        SHIFT[i] = m;
    }
    for(j = m-2; j >= 0; --j){
        if(SHIFT[T[j]] == m)
            SHIFT[T[j]] = m - (j+1);
    }
    while(!feof(s)){
        for(k = 0; k < m; ++k){
            if(T[k] != (c = fgetc(s)))
                break;
            if(feof(s))
                break;
        }
        if(k >= m){
            ++counter;
            pos += m;
            continue;
        }
        if(feof(s))
                break;
        fseek(s, pos + (m - 1), SEEK_SET);
        c = fgetc(s);
        if(feof(s))
                break;
        pos += SHIFT[c];
        fseek(s, pos, SEEK_SET);
    }
    fseek(s, start, SEEK_SET);
    return counter;
}


int main(void){
    const BYTE *T = "637";
    FILE *fi;
    if((fi = fopen("input.txt", "rb")) == NULL){
        printf("cant open file");
        return 0;
    }
    //setvbuf(fi, NULL, _IOFBF, 1000000);
    int t = (int) clock();
    printf("%i\n", search_BMH(T, strlen(T), fi));
    printf("%i\n", (int)clock() - t);
    t = (int) clock();

    printf("%i\n", search_naive(T, strlen(T), fi));
    printf("%i\n", (int)clock() - t);

    close(fi);

    return 0;
}
