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
    slinkedlist *newElem = malloc(sizeof(struct slinkedlist)); // new element

    // fill the new element
    newElem->value = value;
    newElem->next = NULL;

    // if newlist is still not assigned
    // assign it and end the process
    if(iter == NULL)
    {
        newList = newElem;
        return 0;
    }

    // if we have a first element we can work with that
    while(iter->next != NULL)
    {
        // if the value exists we dont inssert as we dont want doublicates
        if(iter->value == value)
        {
            free(newElem);
            return -1;
        }
        // iterate to the last element that doenst have a next element yet
        iter = iter->next;
    }

    // assign the newly created element to the next in line
    iter->next = newElem;

	return 0;
}

static int removeElement(void) {
	// TODO: implement me!
    if(newList != NULL)
    {
        newList = newList->next;
    }
	return 0;
}

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

int main (int argc, char* argv[]) {

	printf("insert 47: %d\n", insertElement(47));
	printf("insert 11: %d\n", insertElement(11));
	printf("insert 23: %d\n", insertElement(23));
	printf("insert 11: %d\n", insertElement(11));

    printList();

	printf("remove: %d\n", removeElement());
	printf("remove: %d\n", removeElement());

	// TODO: add more tests
    printList();

	exit(EXIT_SUCCESS);
}
