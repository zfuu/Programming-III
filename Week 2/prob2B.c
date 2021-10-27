#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define N 4096

int main(int argc, char *argv[]){
    char buf[N];
    char c;
    int fd, i, j, n, k=0, count=0;
    int len = strlen(argv[1]);
    // printf("len = %d\n",len);
    for (i = 2; i < argc; i++) {
        if ((fd = open(argv[i], O_RDONLY)) < 0) {
            fprintf(stderr, "cannot open %s\n", argv[i]);
            continue;
        }
 
        while ((n = read(fd, buf, N)) > 0) {
            // printf("\n");
            // printf("%d\n",n);
            // printf("%s\n", buf);
            buf[n] = ' ';
            for (j = 0; j < n; j++) {
                // state diagram to count the appearance of argv[1]
                c = tolower(buf[j]);
                // printf("%d%c ", k,c);
                // printf("%d[%c?%c]%d//[%c] ", j,c,argv[1][k],k,buf[j+1]);
                
                // printf("%c", buf[j]);
                if (c == argv[1][k]){
                    // printf("%c", c);
                    k += 1;
                    // if ((k == len && !isalpha(buf[j+1])) || j==N && k>0){
                    // if (j != n-1){
                        if ((k == len && !isalpha(buf[j+1]))){
                            count ++;
                            k = 0;
                            // printf("counttttted!");
                        }
                    
                    // }
                    


                }else if (c != argv[1][k]){
                    k = 0;
                }  
            }            
        }
        close(fd);
    }

    printf("\n\n");
    printf("%d\n", count);
}