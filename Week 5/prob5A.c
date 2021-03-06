#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>

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

int main(int argc, char *argv[]){

    struct cell{
        char *word;
        struct cell *next;
    } *list = NULL, *p, *q;
    FILE *fp;
    int i;
    char buf[1024];

    for (i = 1; i < argc; i++) {
        if ((fp = fopen(argv[i], "r")) == NULL) {
            fprintf(stderr, "cannot open %s\n", argv[i]);
            exit(1);
        }

        while (get_word(fp, buf) != 0){

            p = (struct cell *)malloc(sizeof(struct cell));
            p->word = (char *)malloc(strlen(buf+1));
            strcpy(p->word, buf);
            p->next = list;
            list = p;
        }
        fclose(fp);
    }

    
    for(p=list; p != NULL; p = p->next){
        
        for (q = p->next; q != NULL; q = q->next){
            if (strcmp(p->word, q->word)>0){
                char *temp = p->word;
                p->word = q->word;
                q->word = temp;

            }
        }


        printf("%s \n", p->word);

    }
    

}