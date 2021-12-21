#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>

#define N 1024
#define L 256

struct word_pair{
        char *w[2];
    } a[N];
char buf[2][L];


FILE *fp;
int i,j,k;


int get_word(FILE *fp, char buf[]){
    int ch, k = 0;

    while (!isalpha(ch = getc(fp)) && ch != EOF);
    if (ch == EOF) return 0;
    
    buf[k++] = ch;
    while ((ch = getc(fp)) != EOF && isalpha(ch))
        buf[k++] = ch; 
        buf[k] = '\0';
    return 1; 
}

int cmp(const void *p, const void *q){
    int v;
    struct word_pair *a = (struct word_pair *)p;
    struct word_pair *b = (struct word_pair *)q;

    if((v = strcmp(a->w[0], b->w[0])) == 0){
        return strcmp(b->w[1], a->w[1]);
    }else{
        return v;
    }

}


int main(int argc, char *argv[]){


    for (i = 1; i < argc; i++) {
        if ((fp = fopen(argv[i], "r")) == NULL) {
            fprintf(stderr, "cannot open %s\n", argv[i]);
            continue;
        }

        // while (get_word(fp, buf[0]) || get_word(fp, buf[0])){
        while (get_word(fp, buf[0])){
        while (get_word(fp, buf[1])){
        // while (get_word(fp, buf[j])){


            for(j = 0; j < 2; j++){
                a[k].w[j] = (char *)malloc(strlen(buf[j])+1);
                strcpy(a[k].w[j], buf[j]);
            }
            k++;
        }
        }
        fclose(fp);
    }
    
    qsort(a, k, sizeof(struct word_pair), cmp);

    // printf("%s\n", "aaaaa");

    for (i = 0; i < k; i++){
        printf("%s, %s\n", a[i].w[0], a[i].w[1]);
        // printf("%s\n", a[i].w[0]);

    }

}