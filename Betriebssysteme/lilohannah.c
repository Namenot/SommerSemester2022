#include <stdio.h>
#include <stdlib.h>

// general concept: head node points to newest element but inst a node, its only a var
// nodes always point to their previous node (newer nodes point to older ones)

struct listelement
{
        int data;
        struct listelement *next;
};
typedef struct listelement listelement;
 
listelement *list_head = NULL; //points to newest element


int insertElement(int value)
{
    if(value < 0){ return -1;} // only non-neg ints allowed

    listelement *node = list_head; //node that is currently head, check if this pointer is correct
    // allocate memeory with malloc
    listelement *newElement = malloc(sizeof(listelement));
        
    if(newElement == NULL) {
        //some error handleing in case of no space available should go here
        return -1;
    }

    // fill newElement if memory allocation was successful
    newElement->data = value;
    newElement->next = NULL;

    if(node != NULL)
    {

        // check if new
        while(node->next != NULL){
            if(node->data == value)
            {
                free(newElement); // free the allocated memory as we dont need it
                return -1; // if value is already in list then return
            } 
            node = node->next; // go to next node

        }
        
        // everything went according to plan so far, so actually do insert
        newElement->next = list_head; //newElement points to previous newest element        
    }

    list_head = newElement;

    return 0;
}

int removeElement(void){
    if (list_head == NULL){return -1;} //if list empty 
    else{
        listelement *node = list_head;
        listelement *previous = NULL; // keep track of element previous to the one we are currently looking at
        // search oldest element by backtracking from newest one
        while(node->next != NULL){
            previous = node;
            node = node->next;
        }
        previous->next = NULL; //remove reference to deleted node
        // free allocated memory
        free(node);
        return 0;
    }
}

void printList()
{
    listelement *iter = list_head; // iterator pointer that allows me to go through the list
    while(iter != NULL)
    {
        printf(":%d ", iter->data);
        iter = iter->next;
    }
    printf("\n");
}

int main(void) {
    // Write C code here
    printf("Hello world\n"); // is this the right place for this struct?

    printf("inserting: 1 :%d\n", insertElement(1));
    printf("inserting: 2 :%d\n", insertElement(2));
    printf("inserting: 3 :%d\n", insertElement(3));
    printf("inserting: 4 :%d\n", insertElement(4));
    printf("inserting: 5 :%d\n", insertElement(5));
    printf("inserting: 5 :%d\n", insertElement(5));
    printf("inserting: 6 :%d\n", insertElement(6));

    printf(" -------------- \n");

    printList();

    printf(" -------------- \n");

    printf("removing the oldest element: %d\n", removeElement());
    printf("removing the oldest element: %d\n", removeElement());
    printf("removing the oldest element: %d\n", removeElement());
    printf("removing the oldest element: %d\n", removeElement());

    printList();

    return 0;
}