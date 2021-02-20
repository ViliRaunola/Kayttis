#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

void read_file(char *file_name);

int main(int argc, char *argv[]){

    fprintf(stdout, "You gave this many variables: %d.\n", argc);
    fprintf(stdout, "The second variable was: %s\n", argv[1]);

	
	read_file(argv[1]);

    frpintf(stdout, "Thank you for using this program!\n");

    return(0);
}


//opens the file that user gave 
void read_file(char *file_name){

    char *line = NULL;
    size_t n = 0;
    

    FILE *f = fopen(file_name, "r");
    if(f == NULL){
        fprintf(stderr, "error: cannot open file '%s'\n", file_name);
        exit(1);
    }
    
    fprintf(stdout, "The file '%s' contains:\n\n", file_name);

    //getline() automatically updates the size of 'line' and 'n' to
    //fit the line that is beign read. They must be set to NULL and 0 before calling.
    //returns -1 when exiting.
    //Source: man getline
    while(getline(&line, &n, f) != -1){ 
        fprintf(stdout, "%s", line);
    }

    free(line);
    fclose(f);
}


/*#########################***EOF***#########################*/