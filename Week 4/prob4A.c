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

struct node{
    char *word;
    int count;
    struct node *left;
    struct node *right;
};

struct node *alloc_node(char *word){
    struct node *p;

    p = (struct node *)malloc(sizeof(struct node));
    p->word = (char *)malloc(strlen(word) + 1);
    strcpy(p->word, word);
    p->count = 1;
    p->left = NULL;
    p->right = NULL;


    return p;
}

void print_tree(struct node *p){

    if (p->left != NULL)
        print_tree(p->left);
    printf("%s %d\n", p->word, p->count);

    if (p->right != NULL)
        print_tree(p->right);
}

int main(int argc, char *argv[]){

    int i, v;
    struct node *root = NULL, *p;
    char buf[1024];
    FILE *fp;

    for (i = 1; i < argc; i++){

        if ((fp = fopen(argv[i], "r")) == NULL){
            fprintf(stderr, "cannot open %s\n", argv[i]);
            exit(1);
        }

        while (get_word(fp, buf) != 0){
            if (root == NULL){
                root = alloc_node(buf);
            }else{
                for (p = root;;){
                    if ((v = strcmp(buf, p->word)) == 0){
                        p->count++;
                        break;
                    }else if (v < 0){
                        if (p->left == NULL){
                            p->left = alloc_node(buf);
                            break;
                        }else{
                            p = p->left;
                        }  
                    }else{
                        if (p->right == NULL){
                            p->right = alloc_node(buf);
                            break;
                        }else{
                            p = p->right;
                        }
                    }
                }
            }
        }
        fclose(fp);
    }
    print_tree(root);
}