#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct for the linked list
struct node {
    char *line;
    struct node *next_node, *previous_node; //has pointer for the next and previous node in the list so it can be also reversed
};

struct node* read_file(char *file_name, struct node *start_node);
struct node* new_node(struct node *last_node, char *read_line);
struct node* backtrack_to_front_and_connect_next_node(struct node* last_node);
struct node* free_linked_list(struct node *start_node);
void print_linked_list(struct node *start_node);

int main(int argc, char *argv[]){
    struct node *start_node = NULL;
    char input[] = "input.txt";
    
    fprintf(stdout, "You gave this many variables: %d.\n", argc);
    fprintf(stdout, "The second variable was: %s\n", argv[1]);
	start_node = read_file(input, start_node);
    fprintf(stdout, "Now printing the linked list:\n\n");
    print_linked_list(start_node);

    start_node = free_linked_list(start_node);
    fprintf(stdout, "Thank you for using this program!\n");
    return(0);
}


//opens the file that user gave 
struct node* read_file(char *file_name, struct node *start_node){
    char *line = NULL;
    size_t n = 0;
    struct node *temp_node;
    struct node *prev_node = start_node;
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
        temp_node = new_node(prev_node, line);  //when the loop is done prev_node has the address of the last node in the linked list
        prev_node = temp_node;
    }
    free(line);
    fclose(f);

    return(start_node = backtrack_to_front_and_connect_next_node(prev_node));
}

//creates a new struct for the linked list and connects it to the previous node in the linked list
struct node* new_node(struct node *last_node, char *read_line){
    struct node *ptr_new_node = NULL;
    if( (ptr_new_node = (struct node*)(malloc(sizeof(struct node)))) == NULL){
        fprintf(stderr, "malloc failed");
        exit(1);
    }
    //if the last_node doesn't exist, assign null to the previous_node
    if(last_node != NULL){ 
        ptr_new_node->line = malloc(strlen(read_line)+1); //at first I just copied just the memory address but then I realized I had to allocate memory and copy the read string to the newly allocated memory
        if((ptr_new_node->line) == NULL){
            fprintf(stderr, "malloc failed");
            exit(1);
        }
        strcpy(ptr_new_node->line, read_line);
        ptr_new_node->next_node = NULL;
        ptr_new_node->previous_node = last_node;
    }else{
        ptr_new_node->line = malloc(strlen(read_line)+1);
        if((ptr_new_node->line) == NULL){
            fprintf(stderr, "malloc failed");
            exit(1);
        }
        strcpy(ptr_new_node->line, read_line);
        ptr_new_node->next_node = NULL;
        ptr_new_node->previous_node = NULL;
    }
    return ptr_new_node;
}

//iterates through the linked list from the back to the front
struct node* backtrack_to_front_and_connect_next_node(struct node* last_node){
    struct node *temp;
    while((last_node->previous_node) != NULL){
        temp = last_node;
        last_node = temp->previous_node;
        last_node->next_node = temp;
    }
    return last_node;
}

//goes through the linked list and frees every node it has
//returns the start node which will be NULL
struct node* free_linked_list(struct node *start_node){
    struct node *node = start_node;
    while(node != NULL){
        start_node = node->next_node;
        free(node->line);   //remember to free all the memory that was allocated with malloc
        free(node);
        node = start_node;
    }
    return start_node;
}

void print_linked_list(struct node *start_node){
    while(start_node != NULL){
        fprintf(stdout, "%s", start_node->line);
        start_node = start_node->next_node;
    }
}

/*#########################***EOF***#########################*/