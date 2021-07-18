/* LinkedList Declaration */
#include <stdlib.h>
#include <stdbool.h>

/* Constants */
#define LL_INDEX_ERROR_MSG "linked_list:IndexError: %d out of bounds with linked list of length %d"
#define LL_MEM_ALLOC_ERROR_MSG "linked_list:AllocationError: Could not allocate memory of size: %d"
#define LL_ACESS_EMPTY_LIST "linked_list:Tried to access an empty linked list"
#define LL_NULL_POINTER_NODE "linked_list:Node at index: %d the list is NULL"


/* Structures */

// Node structure
typedef struct Node
{
	void* value;
	struct Node *next;
} Node;

// Linked List structure
typedef struct LinkedList
{
	int length;
	size_t value_size;
	Node *head;
	bool _initialized;
} LinkedList;


/* 'Private' Methods */

// error message
void _exit_msg(const char* msg);

// initialize the list
void _init_list(LinkedList *list, void* value);

// is an index valid ?
bool _valid_index(LinkedList *list, int index, bool include_end);

// assert that an index is valid
void _assert_index(LinkedList *list, int index, bool include_end);

// get the node at the index
Node* _get_node_at(LinkedList *list, int index);

// create a new node
Node* _new_node();


/* 'Public' Methods */

// get value at index
void* get_value_at(LinkedList *list, int index);

// insert value at index
void insert_value_at(LinkedList *list, void* value, int index);

// remove value at index
void* remove_value_at(LinkedList *list, int index);

// remove value
int remove_value(LinkedList *list, void* value);

// append value
void append_value(LinkedList *list, void* value);
