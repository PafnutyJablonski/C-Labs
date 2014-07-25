#include <stdio.h>
#include <string.h>

#define ALPH_SIZE (256)

int encoder_caesar(FILE *in, FILE *out, char *k){
    int  counter, i, len;
    char c, cout;
    len = strlen(k);
    i = 0;
    c = fgetc(in);
    while(!feof(in)){
        cout = (c + k[i % len]) % ALPH_SIZE;
        fputc(cout, out);
        ++i;
        c = fgetc(in);
    }
    return 0;
}

int decoder_caesar(FILE *in, FILE *out, char *k){
    int  counter, i, len;
    char c, cout;
    len = strlen(k);
    i = 0;
    c = fgetc(in);
    while(!feof(in)){
        cout = (c - k[i % len]) % ALPH_SIZE;
        fputc(cout, out);
        ++i;
        c = fgetc(in);
    }
    return 0;
}

int main(void){
    FILE *fi, *fo;
    if((fi = fopen("output.txt", "rb")) == NULL){
        printf("cant open file");
        return 0;
    }
    if((fo = fopen("test.c", "wb")) == NULL){
        printf("cant open file");
        return 0;
    }
    char* key = "abcdsh";
    decoder_caesar(fi, fo, key);
    return 0;
}
