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
        int count;
        struct cell *next;
    } *list = NULL, *p;
    FILE *fp;
    int i;
    char buf[1024];

    struct cell *q;
    struct cell *sorted_list;


    for (i = 1; i < argc; i++) {
        if ((fp = fopen(argv[i], "r")) == NULL) {
            fprintf(stderr, "cannot open %s\n", argv[i]);
            exit(1);
        }

        while (get_word(fp, buf) != 0){
            for (p = list; p != NULL; p = p->next){
                if (strcmp(buf, p->word) == 0){
                    p->count++;
                    goto next;
                }
            }
            p = (struct cell *)malloc(sizeof(struct cell));
            p->word = (char *)malloc(strlen(buf+1));
            strcpy(p->word, buf);
            p->count = 1;
            p->next = list;
            list = p;

            next:;
        }
        fclose(fp);
    }

    
    for(p=list; p != NULL; p = p->next){
        printf("%s %d\n", p->word, p->count);
    }
    
    // *sorted_list = *list;


    
    // while (list != NULL){
    //     p = list;
    //     list = list;
    //     q = sorted_list;

    //     while(q->next != NULL){
    //         if (q->next->count < p->count){
    //             q->word = p->word;
    //             q->count = p->count;
    //             q->next = sorted_list;
    //             sorted_list = q;
    //         }
    //     }



    //     sorted:;
    //     break;
    // }

    // // for(p=list; p != NULL; p = p->next){
    // //     printf("%s %d\n", p->word, p->count);
    // // }

    // for(q=sorted_list; q != NULL; q = p->next){
    //     printf("%s %d\n", q->word, q->count);
    // }


    

    

}