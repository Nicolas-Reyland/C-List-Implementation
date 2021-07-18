/* LinkedList Implementation */
#include <stdlib.h>
#include <stdbool.h>

// Node structure
typedef struct Node
{
	void* value;
	struct Node *next;
} Node;

// Linked List structure
typedef struct LinkedList
{
	bool _initialized;
	int length;
	size_t element_size;
	Node *head;
} LinkedList;


/* 'Private' Methods */

// initialize the list
void _init_list(LinkedList *list, void* element);

// is an index valid ?
bool _valid_index(LinkedList *list, int index);

// assert that an index is valid
void _assert_index(LinkedList *list, int index);

// get the element at the index
Node* _get_element_at(LinkedList *list, int index);

// create a new node
Node* _new_node();


/* 'Public' Methods */

// get element at index
void* get_element_at(LinkedList *list, int index);

// insert element at index
void insert_element_at(LinkedList *list, void* element, int index);

// remove element at index
void* remove_element_at(LinkedList *list, int index);

// remove element
int remove_element(LinkedList *list, void* element);

// append value
void append_element(LinkedList *list, void* element);
