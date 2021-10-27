#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define N 4096

int main(int argc, char *argv[]){
    char buf[N];
    int fd, i, j, n, k=0, count=0;
    int len = strlen(argv[1]);
    for (i = 2; i < argc; i++) {
        if ((fd = open(argv[i], O_RDONLY)) < 0) {
            fprintf(stderr, "cannot open %s\n", argv[i]);
            continue;
        }
        while ((n = read(fd, buf, N)) > 0) {
            for (j = 0; j < n; j++) {
                // state diagram to count the appearance of argv[1]
            }
        }
        close(fd);
    }
    printf("%d\n", count);
}