/* LinkedList Struct */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/* YOU NEED TO typedef THE LINKED_LIST_TYPE YOU WANT TO USE FOR THIS StaticList
 * Example:

 * typedef char LINKED_LIST_TYPE; // typedef the LINKED_LIST_TYPE you want to use (here char, but could any type (even structs/unions/etc.))
 * #include "LinkedList.h" // include the LinkedList.h header

 * Now, you can use LinkedLists using type char.
 * To be able to use multiple data_types (one data_type per LinkedList),
 * please use the generate_linked_list_headers.py
 *
 */

#define typename(x) _Generic((x),		/* Get the name of a type */					\
																						\
			_Bool: 0,				  unsigned char: 1,				\
			 char: 2,					 signed char: 3,				\
		short int: 4,		 unsigned short int: 11,	 		\
			  int: 5,					 unsigned int: 12,				\
		 long int: 6,		   unsigned long int: 13,	 		\
	long long int: 7, unsigned long long int: 14,	\
			float: 8,						 double: 10,				 		\
	  long double: 9,				   char *: 15,			\
		   void *: 16,				int *: 17,			\
		  default: 18)

/* The Node is an element of a LinkedList */
struct Node {
	LINKED_LIST_TYPE value;
	struct Node *next;
};

/* LinkedList */
typedef struct LinkedLists { // maybe add a member 'last', pointing to the last member of the list (so some operations can be done faster/easier)
	int num_elements; // dont need this in theory, but saves some calculation time in some functions
	size_t size;
	struct Node *head;
} LinkedList;

/* Check if a given index is valid (for insertion) */
void _checkIndex(LinkedList *list, int index) {
	if (index > list->num_elements) {
		fprintf(stderr, "Index out of bounds. Exiting\n");
		exit(EXIT_FAILURE);
	}
}

/* Returns the Node at index 'index' of the LinkedList */
struct Node* _getNodeAtIndex(LinkedList *list, int index) {
	// take the head
	struct Node *element = list->head;
	// go from element to element until the index is reached
	for (int i = 0; i < index; i++) {
		element = element->next;
	}
	// return last element found
	return element;
}
/* Create a new node using malloc, so every node can be freed */
struct Node* _newNode() {
	// allocate new memory for node
	struct Node *node = (struct Node*) malloc(sizeof(struct Node));
	// if the pointer is NULL, the allocation faled
	if (node == NULL) {
		fprintf(stderr, "Memory allocation for new node failed. Exiting\n");
		exit(EXIT_FAILURE);
	}
	return node;
}

/* intialize a LinkedList (set num_elements, size & head) with a value */
void initListAtValue(LinkedList *list, LINKED_LIST_TYPE value) {
	list->num_elements = 1;
	list->size = sizeof(LINKED_LIST_TYPE);
	list->head = _newNode(); // so it can be freed ('free(node)') like al the rest
	list->head->value = value;
	list->head->next = NULL;
}

/* Returns the value of the nth element of the LinkedList */
LINKED_LIST_TYPE getValueAtIndex(LinkedList *list, int index) {
	// check if index in valid
	_checkIndex(list, index);
	// get the nth Node of the list
	struct Node *node = _getNodeAtIndex(list, index);
	// returns its value
	return node->value;
}

/* insert a value at index 'index' in the LinkedList */
void insertValueAtIndex(LinkedList *list, LINKED_LIST_TYPE value, int index) {
	// check if the index is valid
	_checkIndex(list, index);
	// create a new node with value 'value'
	struct Node *current = _newNode();
	current->value = value;

	// insert at he beginning
	if (index == 0) {
		current->next = list->head;
		// point the head of the list to this node
		list->head = current;
	} else
	// insert at the end of linked list
	if (index == list->num_elements) {
		// get the node before the 'index'
		struct Node *prev = _getNodeAtIndex(list, index - 1);
		// point the 'prev' node to the 'current' node
		prev->next = current;
		// point the 'current' node to NULL (end of lniked list)
		current->next = NULL;
	} else
	// insert somewhere in the list (except borders)
	{
		// get previous node
		struct Node *prev = _getNodeAtIndex(list, index - 1);
		// get the node that should come after this node (which is at the current index)
		struct Node *next = _getNodeAtIndex(list, index);
		// point the current node to the node that was at 'index'
		current->next = next;
		// point the 'prev' node to the 'current' node
		prev->next = current;
	}
	list->num_elements++;
}

/* Removes the Node at index 'index'. Returns it's value */
LINKED_LIST_TYPE removeValueAtIndex(LinkedList *list, int index) {
	// check if index is valid (extra line bc first testing with index + 1)
	_checkIndex(list, index + 1); if (index == -1) {_checkIndex(list, -1);}
	// declare current node (the one to be removed)
	struct Node *current;

	// remove first element
	if (index == 0) {
		// get head of LinkedList
		current = list->head;
		// change the list head
		list->head = current->next;
	} else
	// remove from anywhere int the list (except start)
	{
		// get the previous node
		struct Node *prev = _getNodeAtIndex(list, index - 1);
		// get the current node
		current = prev->next;
		// link the previous to the next
		prev->next = current->next;
	}

	// extract value of current (removed node)
	LINKED_LIST_TYPE value = current->value;
	// free the memory of removed node
	free(current);
	// decrement num_elements
	list->num_elements--;

	return value;
}

void addValueAtEnd(LinkedList *list, LINKED_LIST_TYPE value) {
	// get last node of the Linked list
	struct Node *last = _getNodeAtIndex(list, list->num_elements - 1);
	// create new node with value 'value' and pointing to NULL (end of list)
	struct Node *current = _newNode();
	current->value = value;
	current->next = NULL;
	// point the previous last node to the new one
	last->next = current;
	// increment
	list->num_elements++;
}

/* Prints a LinkedList */
void printLinkedList(LinkedList *list) {
	/* Can print the folowing types:
	 * char
	 * strings (arrays of char)
	 * signed char
	 * unsigned char
	 * short (short int, signed short, signed short int)
	 * unsigned short (unsigned short int)
	 * int (signed, signed int)
	 * long (long int, signed long, signed long int)
	 * long long (long long int, signed long long int)
	 * unsigned long (unsigned long int)
	 * unsigned long long (unsigned long long int)
	 * float
	 * double
	 * long double
	 * _Bool
	 * pointers to void, char & int
	 *
	 * for all other types, it will print them as integers
	 */

	// is the list empty ?
	if (list->num_elements == 0) {
		printf("The List is empty\n");
		return;
	}

	// declare a varaible with type LINKED_LIST_TYPE
	LINKED_LIST_TYPE elem;

	// get the type name
	int type_ = typename(elem);

	char symbol[6];
	if (type_ == 0) { // _Bool
		strcpy(symbol, "%d");
	} else if (type_ < 4) { // unsigned char + char + signed char
		strcpy(symbol, "%c");
	} else if (type_ < 8) { // short int, int, long int, long long int
		strcpy(symbol, "%lld");
	} else if (type_ < 11) { // float + double + long double
		strcpy(symbol, "%llf");
	} else if (type_ < 15) { // unsigned (short int, int, long int, long long int)
		strcpy(symbol, "%llu");
	} else if (type_ < 18) { // pointer to (void, int, char)
		strcpy(symbol, "%x");
	} else if (type_ == 18) { // other
		// printf("Type not found. Using default \%d\n");
		strcpy(symbol, "%d");
	} else {
		fprintf(stderr, "Invalid type integer: %d. Exiting\n", type_);
		exit(EXIT_FAILURE);
	}

	char str[] = "List[%d] = ";
	strcat(str, symbol);
	strcat(str, "\n");

	// print every element
	struct Node *element = list->head;
	for (int i = 0; i < list->num_elements; i++) {
		printf(str, i, element->value);
		element = element->next;
	}
}
