#include <stdio.h>
#include <stdlib.h>

int main(void){
    int *A, i, j, m, n;
    double a, b, res;
    char c;
    FILE *fi, *fo;
    if((fi = fopen("input.txt", "rt")) == NULL){
        printf("cant open file");
        return 0;
    }
    if((fo = fopen("output.txt", "wt")) == NULL){
        printf("cant open file");
        return 0;
    }
    fscanf(fi, "%lf", &a);
    while(!feof(fi)){
        //c = ' ';
        c = fgetc(fi);
        while(c != '+' && c != '-' && c != '*' && c != '/')
            c = fgetc(fi);
        fscanf(fi, "%lf", &b);
        switch(c) {
            case '+':
                fprintf(fo, "%lf ", a + b);
                a = b;
                break;
            case '-':
                fprintf(fo, "%lf ", a - b);
                a = b;
                break;
            case '*':
                fprintf(fo, "%lf ", a * b);
                a = b;
                break;
            case '/':
                if(b == 0){
                    fprintf(fo, "%i ", 0);
                }else fprintf(fo, "%lf ", a / b);
                a = b;
                break;
            default:
                printf("Error");
                return 1;
        }

    }
    close(fi);
    close(fo);
    return 0;
}
