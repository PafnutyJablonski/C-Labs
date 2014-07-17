#include <stdio.h>

int encoder_RLE(FILE *in, FILE *out){
    int  counter, i;
    unsigned char c, cur, next, s;
    counter = 0;
    c = fgetc(in);
    while(!feof(in)){
        next = fgetc(in);
        if(c == next){
            fputc(c, out);
            fputc(c, out);
            while((next = fgetc(in)) == c){
                if (feof(in)) break;
                ++counter;
                if(counter == 255){
                    next = fgetc(in);
                    break;
                }
            }
            fputc(counter, out);
            counter = 0;
        }else{
            fputc(c, out);
            if (feof(in)) break;
        }
        c = next;
    }
    return 0;
}

int decoder_RLE(FILE *in, FILE *out){
    int counter, i;
    unsigned char c, cur, next, s;
    counter = 0;
    c = fgetc(in);
    while(!feof(in)){
        next = fgetc(in);
        if(c == next){
            fputc(c, out);
            fputc(next, out);
            if (feof(in)) break;
            counter = fgetc(in);
            for(i = 0; i < counter; ++i)
                fputc(c, out);
            if (feof(in)) break;
            next = fgetc(in);
        }else{
            fputc(c, out);
            if (feof(in)) break;
        }
        c = next;
    }
    return 0;
}

int main(){
    FILE *fi, *fo;
    if((fi = fopen("input.txt", "rb")) == NULL){
        printf("cant open file");
        return 0;
    }
    if((fo = fopen("output.txt", "wb")) == NULL){
        printf("cant open file");
        return 0;
    }
    decoder_RLE(fi, fo);
    close(fi);
    close(fo);
    return 0;
}
