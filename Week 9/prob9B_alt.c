#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/dir.h>
#include<dirent.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

char currentdir[2048] = "";
char basedir[2048] = "";

int dirDepth(char *dir){
    int count = 0;
    char *pch=strchr(dir,'/');
    while (pch!=NULL) {
        count++;
        pch=strchr(pch+1,'/');
    }

    return count;
}

void backDir(char* dir){
    char *del = &dir[strlen(dir)];
    while (del > dir && *del != '/')
        del--;

    if (*del== '/')
        *del= '\0';
    return;
}

void searchDir(char *filename, char *dirname, int depth){
    
    DIR *dir;

    struct dirent *direntp;
    dir=opendir(dirname);
    chdir(dirname);
    
    while((direntp=readdir(dir))!=NULL){
        
        if (direntp->d_name[0] == '.') continue;

        if(direntp->d_type==4){
            strncat(currentdir, "/", sizeof(currentdir) - strlen(currentdir) - 1);
            strncat(currentdir, direntp->d_name, sizeof(currentdir) - strlen(currentdir) - 1);
            searchDir(filename, direntp->d_name, depth+1);

        }else{
            if (strcmp(direntp->d_name, filename) == 0){
                printf("FOUND %s%s/%s\n",basedir, currentdir, filename);
            }
        }
    }
    for (int i = 0; i <= dirDepth(currentdir)-depth; i++) backDir(currentdir);
    chdir("..");
    closedir(dir);
}


int main(int argc, char *argv[]){
    // printf("%d\n", argc);
    if (argc <= 2){
        searchDir(argv[1], ".", 0);
    }else{
        for (int i = argc-1; i >= 2; i--) {
            memset(basedir,0,strlen(basedir));
            strncat(basedir, argv[i], sizeof(basedir) - strlen(basedir) - 1);
            searchDir(argv[1], argv[i], 0);
        }
    }
    return 0;
}