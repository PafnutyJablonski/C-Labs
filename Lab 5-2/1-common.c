#include <stdio.h>

int main(){
    FILE *fi, *fo;
    char **S, *str;
    unsigned char c;
    int cnt, i, j, k, fsize, m, maxs, n, r, t, y, w, z;
    long h = 0;
    if((fi = fopen("input.txt", "rt")) == NULL){
        printf("cant open file");
        return 0;
    }

    n = 1;

    while(!feof(fi)){
        if(fgetc(fi) == '\n') ++n;
    }
    S = (char*) malloc(sizeof(char*) * n);
    fseek(fi, 0, SEEK_SET);
    maxs = 0;
    m = 0;
    i = 0;
    while(!feof(fi)){
        str =(char*) malloc(1);
        while((c = fgetc(fi)) != '\n'){
            str[m] = c;
            ++m;
            str = (char*)realloc(str, sizeof(char) * (m+1));
            if(feof(fi)) break;
        }
        maxs = (maxs < m)?(m):(maxs);
        str[m] = 0;
        S[i] = str;
        ++i;
        m = 0;
        str = NULL;
    }
    for(i = 0; i < n; ++i){
        printf("%s\n", S[i]);

    }
    fsize = 15 * maxs;
    w = (fsize%4 == 0)?(fsize):(fsize + 4 - fsize % 4);
    fsize = w * n + 54;
    printf("%i\n", fsize);
    close(fi);
    if((fo = fopen("out.bmp", "wb")) == NULL){
        printf("cant open file");
        return 0;
    }
    fputc('B', fo);
    fputc('M', fo);
    fwrite(&fsize,4,1,fo);
    r = 0;
    fwrite(&fsize, 4, 1, fo);
    r = 54;
    fwrite(&r, 4, 1, fo);
    r = 40;
    fwrite(&r, 4, 1, fo);
    r = 5 * maxs;
    fwrite(&r, 4, 1, fo);
    r = 5 * n;
    fwrite(&r, 4, 1, fo);
    r = 1;
    fwrite(&r, 2, 1, fo);
    r = 24;
    fwrite(&r, 2, 1, fo);
    r = 0;
    for(i = 0; i < 6; ++i){
        fwrite(&r, 4, 1, fo);
    }
    cnt = 0;
    k = 0;
    for(i = n-1; i >= 0; --i){
        for(y = 0; y < 5; ++y){
            cnt = 0;
            while(S[i][k] != 0){
                for(z = 0; z < 5; ++z){
                    for(j = 0; j < 3; ++j){
                        fputc(S[i][k], fo);
                        ++cnt;
                    }
                }
                ++k;
            }
            k = 0;
            if((w - cnt) != 0){
            for(j = 0; j < w - cnt; ++j)
                fputc(0, fo);
            }
        }

    }



    close(fi);
    close(fo);
    return 0;
}
