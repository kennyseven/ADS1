#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX 250

struct node {
    char data;
    int weight;
    int end_of_key;
    struct node *left;
    struct node *equal;
    struct node *right;

};

struct node *insert(struct node *pNode, char *word, int weight);
void traverse(struct node* pNode, char *prefix, char *buffer, int depth);
void find_and_traverse(struct node *pNode, char *prefix);

int
main(int argc, char *argv[]){
    struct node *pNode = NULL;
    char *word;
    char *prefix;
    int weight;

    word = malloc(MAX*sizeof(char));
    if(word == NULL){
        printf("MALLOC FAIL\n");
        exit(EXIT_FAILURE);

    }

    prefix = malloc(MAX*sizeof(char));
    if(prefix == NULL){
        printf("MALLOC FAIL\n");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", argv[0]);
    printf("%s\n", argv[1]);
    printf("%s\n", argv[2]);

    while(scanf("%d;%250[^\n]", &weight, word) != EOF){
        pNode = insert(pNode, word, weight);
    }

    find_and_traverse(pNode, "Melb");

    return 0;
}

/* Function that creates a new node and returns a pointer to that new node */
struct node
*new_node(char *word){
    struct node *new;

    new = malloc(sizeof(struct node));
    if(new == NULL){
        printf("Malloc Failure!\n");
        exit(EXIT_FAILURE);

    }
    new->left = NULL;
    new->equal = NULL;
    new->right = NULL;
    new->data = *word;
    new->end_of_key = FALSE;
    new->weight = 0;

    return new;
}

/* The insert function takes in a pointer to node, a pointer to a word,
and a weight. If the node is empty create a new node. If the word is less,
equal or greater than the current word in pNode, then recursively call the
function to the left, equal or greater. If the word is equal, it also checks
the next word to see if it's nul, then define whether it's end of key or move
on with the next char of the word */

struct node
*insert(struct node *pNode, char *word, int weight){

    if(pNode == NULL){
        pNode = new_node(word);

    }

    if(*word < pNode->data){
        pNode->left= insert(pNode->left, word, weight);

    }else if(*word == pNode->data){
        if(*(word+1) == '\0'){
            pNode->end_of_key = TRUE;
            pNode->weight = weight;


        }else {
            pNode->equal= insert(pNode->equal, word+1, weight);

        }

    }else {
        pNode->right = insert(pNode->right, word, weight);

    }

    return pNode;
}

/* The function takes the pointer to a node and a pointer to an input prefix
if the prefix is not nul nor NULL, then the loop would initiate the
traversing of the tree to the end of the prefix char. At the end of the prefix
char, a traverse function is used to print out all the characters that have
the prefix */

void
find_and_traverse(struct node *pNode, char *prefix){
    char *buffer = NULL;
    char *secondPrefix = prefix;

    buffer = malloc(250*sizeof(char));

    while(*prefix != '\0' && pNode != NULL){

        if(*prefix < (pNode->data)){
            pNode = pNode->left;
            continue;

        }

        if(*prefix > pNode->data){
            pNode = pNode->right;
            continue;

        }

        if(*prefix == pNode->data){
            pNode = pNode->equal;
            prefix = prefix+1;
            continue;

        }
    }

    if(pNode != NULL){
        if(pNode->end_of_key == TRUE){

            /* buffer is a placeholder for the prefix, it adds an extra nul
            char at the end for the next function*/
            buffer[strlen(prefix)] = '\0';
            printf("%s", secondPrefix);
            printf("%s\n", buffer);

        }

        traverse(pNode, secondPrefix, buffer, strlen(prefix));
    }

    return;
}

/* This function traverses through the tree for a given prefix
 * It looks at the left most node and then adds it to the prefix. If the flag
 * is raised, it would be printed out as a word, else it would keep adding.
 * It adds 1 char more at each recursion.
 * It then traverses further in the order of a word */

void
traverse(struct node *pNode, char *secondPrefix, char *buffer, int depth){

    /* if pNode is empty that means there are no further words that
    have the prefix */
    if(pNode == NULL){
        return;

    }

    traverse(pNode->left, secondPrefix, buffer, depth);

    /* the nul char that was added before gets replaced by the new char */
    buffer[depth] = pNode->data;

    if(pNode->end_of_key == TRUE){

        /* since that new character that was added formed a word a new nul
        char is added at the end of the buffer placeholder */
        buffer[depth] = '\0';
        printf("%s", secondPrefix);
        printf("%s\n", buffer);

    }

    /* Depth is the length of the prefix and at each iteration it
    would add 1 more to check if a word exist at that length */
    traverse(pNode->equal, secondPrefix, buffer, depth+1);
    traverse(pNode->right, secondPrefix, buffer, depth);

    return;
}