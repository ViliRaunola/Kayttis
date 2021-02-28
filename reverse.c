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
struct node* backtrack_to_front(struct node* last_node);
struct node* free_linked_list(struct node *start_node);
struct node* read_from_user(struct node *start_node);
void print_linked_list_front_to_back(struct node *start_node);
void go_end_of_list_and_print(struct node* start_node);
void write_linked_to_file(struct node* start_node, char *file_name);

int main(int argc, char *argv[]){
    struct node *start_node = NULL;
    //char input[] = "input.txt";

    if (argc >= 4){
        fprintf(stdout, "usage: reverse <input> <output>\n");
        exit(1);
    }else if (strcmp(argv[1], argv[2]) != 0){
        fprintf(stdout, "Input and output file must differ\n");
        exit(1);
    }else if (argc == 3){
        start_node = read_file(argv[1], start_node);
        write_linked_to_file(start_node, argv[2]);
        start_node = free_linked_list(start_node);
        fprintf(stdout, "Thank you for using this program!\n");
        return(0);
    }else if(argc == 2){
        start_node = read_file(argv[1], start_node);
        go_end_of_list_and_print(start_node);
        start_node = free_linked_list(start_node);
        fprintf(stdout, "Thank you for using this program!\n");
        return(0);
    }else{
        start_node = read_from_user(start_node);
        go_end_of_list_and_print(start_node);
        start_node = free_linked_list(start_node);
        fprintf(stdout, "Thank you for using this program!\n");
        return(0);
    }
    
/*
    fprintf(stdout, "You gave this many variables: %d.\n", argc);
    fprintf(stdout, "The second variable was: %s\n", argv[1]);
	start_node = read_file(input, start_node);
    fprintf(stdout, "Now printing the linked list:\n\n");
    print_linked_list_front_to_back(start_node);

    go_end_of_list_and_print(start_node);

    start_node = free_linked_list(start_node);
    fprintf(stdout, "Thank you for using this program!\n");
    return(0);
*/
}

//opens the file that user gave and reads every line to a double linked list
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
    return(start_node = backtrack_to_front(prev_node));
}

struct node* read_from_user(struct node *start_node){
    char *input = NULL;
    size_t n = 0;
    struct node *temp_node;
    struct node *prev_node = start_node;
    fprintf(stdout, "Give an input to reverse (type ### to stop the input):\n");
    do{
        if(getline(&input, &n, stdin) == -1){
            fprintf(stderr, "getline failed");
            free(input);
            exit(1);
        }
        if(strcmp(input, "###")){
            break;
        }else{
            temp_node = new_node(prev_node, input); //when the loop is done prev_node has the address of the last node in the linked list
            prev_node = temp_node;
        }
    }while (1);
    free(input);
    return(start_node = backtrack_to_front(prev_node));
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
        last_node->next_node = ptr_new_node;
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
struct node* backtrack_to_front(struct node* last_node){
    struct node *temp;
    while((last_node->previous_node) != NULL){
        temp = last_node;
        last_node = temp->previous_node;
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

void print_linked_list_front_to_back(struct node *start_node){
    while(start_node != NULL){
        fprintf(stdout, "%s", start_node->line);
        start_node = start_node->next_node;
    }
}

//iterates to the last node of the linked and goes back to the beginning while printing each nodes' line
void go_end_of_list_and_print(struct node* start_node){
    struct node *temp;
    while((start_node->next_node) != NULL){
        temp = start_node;
        start_node = temp->next_node;
    }
    while(start_node != NULL){
        fprintf(stdout, "%s", start_node->line);
        start_node = start_node->previous_node;
    }
}

//goes to the end of the linked list and prints the list from end to start to the given file
void write_linked_to_file(struct node* start_node, char *file_name){
    struct node *temp;
    FILE *f = fopen(file_name, "w");
    if(f == NULL){
        fprintf(stderr, "error: cannot open file '%s'\n", file_name);
        exit(1);
    }
    while((start_node->next_node) != NULL){
        temp = start_node;
        start_node = temp->next_node;
    }
    while(start_node != NULL){
        fprintf(f, "%s", start_node->line);
        start_node = start_node->previous_node;
    }
    fclose(f);
}

/*#########################***EOF***#########################*/