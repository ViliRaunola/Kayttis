#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    char *file_name_1;
    char *file_name_2;
    char ok[] = "tests-out/5.in";
    char ok2[] = "tests-out/5.in";
    //get only the file name from the input so that the path doesn't get compared 
    //lähde: https://stackoverflow.com/questions/32822988/get-the-last-token-of-a-string-in-c ja man strrchr
    file_name_1 = strrchr(ok, '/')+1;
    file_name_2 = strrchr(ok2, '/')+1;

    if(strcmp(file_name_1, file_name_2) == 0){
        fprintf(stderr, "reverse: input and output file must differ\n"); //instructions and tests error messages differ...
        exit(1);
    }
}