#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;
    int i, ch;
    int state = 0;

    for (i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if ((fp) == NULL) {
            fprintf(stderr, "cannot open %s\n", argv[i]);
            exit(1);
        }
        ch = fgetc(fp);

        while (ch != EOF) {
            if (state == 0){
                // printf ("%c", ch);
                if (ch == '/'){
                    state = 1;
                }else{
                    printf ("%c", ch);
                }
                ch = fgetc(fp);
            }else if (state == 1){
                if (ch == '/'){
                    state = 2;
                }else{
                    state = 0;
                    printf ("/");
                    printf ("%c", ch);
                }
                // printf ("%c", ch);
                ch = fgetc(fp);
            }else{ // state 2
                if (ch == '\n') {
                    state = 0;
                    printf ("%c", ch);
                }
                ch = fgetc(fp);
            }

        }
        fclose(fp);
    }
}