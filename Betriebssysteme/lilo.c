#include <stdio.h>
#include <stdlib.h>

// TODO: structs, global variables, etc.
struct slinkedlist
{
    int value;
    struct slinkedlist *next;
};

typedef struct slinkedlist slinkedlist;
slinkedlist *newList = NULL;


void printList()
{
    slinkedlist *iter = newList; // iterator pointer that allows me to go through the list
    while(iter != NULL)
    {
        printf(":%d ", iter->value);
        iter = iter->next;
    }
    printf("\n");
}

static int insertElement(int value) {
	// TODO: implement me!

    // everything about this is disgusting
    // why am i doing this
    // i kinda hate myself now

    // i guess this works
    // but i need to improove the control flow (ALOT!!!!)


    // we cant not insert negative numbers
    if(value < 0)
        return -1;


    slinkedlist *iter = newList; // iterator pointer that i can modify without destroying the list
    slinkedlist **assignmentptr = &newList; // ptr that will point to the place that we want to paste newElem into

    // if we have a first element we can work with that
    if(newList != NULL)
    {
        while(iter->next != NULL)
        {
            // if the value exists we dont inssert as we dont want doublicates
            if(iter->value == value)
            {
                return -1;
            }
            // iterate to the last element that doenst have a next element yet
            iter = iter->next;
        }

        // overwrite the ptr in
        assignmentptr = &iter->next;
    }

    // if the function hasn't errored yet we now can create a new list entry and allocate memory to it
    slinkedlist *newElem = malloc(sizeof(struct slinkedlist)); // the new list entry

    // was memory allocation successfull?
    if(newElem == NULL)
        return -1;

    // fill the new list entry 
    newElem->value = value;
    newElem->next = NULL;

    // finally insert the new element into the list
    *assignmentptr = newElem;

	return 0;
}

static int removeElement(void) {
	// TODO: implement me!

    // NULL means that no the list is empty thus we dont have any "next element"
    // if an element is the last in the list it points to the NULL pointer
    // as long as we only add new element via the insert function this works
    // however this is really memory unsave if someone would implement their own insertelement 
    // without pointing the next element to NULL
    if(newList != NULL)
    {
        slinkedlist *updateptr;
        updateptr = newList->next; // save the next pointer location 
        free(newList);             // free the memory of the old 1st element
        newList = updateptr;       // assign the new first element
    }
	return 0;
}


int main (int argc, char* argv[]) {

	printf("insert 47: %d\n", insertElement(47));
	printf("insert 11: %d\n", insertElement(11));
	printf("insert 23: %d\n", insertElement(23));
	printf("insert 11: %d\n", insertElement(11));
    printf("insert 12: %d\n", insertElement(12));
    printf("insert 14: %d\n", insertElement(14));
    printf("insert 27: %d\n", insertElement(27));
    printf("insert 16: %d\n", insertElement(16));

    printList();

	printf("remove: %d\n", removeElement());
	printf("remove: %d\n", removeElement());

	// TODO: add more tests

    //printf("remove: %d\n", removeElement());
	//printf("remove: %d\n", removeElement());

    //printf("remove: %d\n", removeElement());
	//printf("remove: %d\n", removeElement());

    printList();

	exit(EXIT_SUCCESS);
}
