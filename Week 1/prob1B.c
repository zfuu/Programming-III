#include<stdio.h> 
#include <string.h>

int main(int argc, char* argv[]){
    char count[128] = {0};
    int longestLength = 0;
    int longestIndex = 0;
    int mostFrequentLetter = 0;
    int frequencyCount = 0;

    for (int i = 1; i <= argc-1; ++i){
        if (strlen(argv[i]) > longestLength){
            longestLength = strlen(argv[i]);
            longestIndex = i;
        }
    }

    for (int j = 0; argv[longestIndex][j] != '\0'; j++){
        count[argv[longestIndex][j]]++;
    }

    for (int k = 0; k < 128; k++){
        if (count[k] > frequencyCount){
            frequencyCount = count[k];
            mostFrequentLetter = k;
        }
    }

    // if (mostFrequentLetter == 0){
    //     printf("");
    // }else{
    //     printf("%c %d", mostFrequentLetter, frequencyCount);
    // }
    printf("%c %d\n", mostFrequentLetter, frequencyCount);

}

