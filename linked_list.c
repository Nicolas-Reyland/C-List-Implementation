/* linked_list Implementation */
#include "linked_list.h"
#include <stdio.h>
#include <errno.h>

// init function
linked_list* init_linked_list()
{
	linked_list* list = (linked_list*) malloc(sizeof(linked_list));
	// setup attributes
	list->length = 0;
	list->value_size = sizeof(void*);
	list->head = NULL;
	// attach methods
	list->get_value_at = &linked_list_get_value_at;
	list->insert_value_at = &linked_list_insert_value_at;
	list->append_value = &linked_list_append_value;
	list->remove_value = &linked_list_remove_value;
	list->remove_value_at = &linked_list_remove_value_at;

	return list;
}

/* Free function */
void free_linked_list(linked_list* list)
{
	_free_linked_list_node(list->head);
	free(list);
}

// free node
void _free_linked_list_node(node* n)
{
	if (n->next != NULL) _free_linked_list_node(n->next);
	free(n);
}


// error message
void _linked_list_exit_msg(const char* msg)
{
	fprintf(stderr, "%s", msg);
	fprintf(stderr, "%s", "\n");
	exit(EXIT_FAILURE);
}

// is an index valid ?
bool _linked_list_valid_index(linked_list *list, int index)
{
	return 0 <= index && index < list->length;
}

// assert that an index is valid
void _linked_list_assert_index(linked_list *list, int index)
{
	if (_linked_list_valid_index(list, index)) return;
	char msg[255];
	sprintf(msg, LL_INDEX_ERROR_MSG, index, list->length);
	_linked_list_exit_msg(msg);
}

// get the value at the index
node* _linked_list_get_node_at(linked_list *list, int index)
{
	node* node = list->head;

	for (int i = 0; i < index; i++)
	{
		node = node->next;
		// verify after we get the next node: the head should have been verified in the _assert_index call
		if (node == NULL)
		{
			char msg[255];
			sprintf(msg, LL_NULL_POINTER_NODE, i);
			_linked_list_exit_msg(msg);
		}
	}

	return node;
}

// create a new node
node* _linked_list_new_node()
{
	// allocate new memory for node
	size_t node_size = sizeof(struct node);
	struct node *node = (struct node*) malloc(node_size);
	// if the pointer is NULL, the allocation faled
	if (node == NULL)
	{
		char msg[255];
		sprintf(msg, LL_MEM_ALLOC_ERROR_MSG, node_size);
		_linked_list_exit_msg(msg);
	}
	return node;
}


/* 'Public' Methods */

// get value at index
void* linked_list_get_value_at(linked_list *list, int index)
{
	_linked_list_assert_index(list, index);
	return _linked_list_get_node_at(list, index)->value;
}

// insert value at index
void linked_list_insert_value_at(linked_list *list, int index, void* value)
{
	// init list ?
	if (index == 0)
	{
		// insert at head
		node* new_head = _linked_list_new_node();
		new_head->value = value;
		new_head->next = list->head;
		list->head = new_head;
	}
	// append after head
	else
	{
		int new_index = index - 1;
		_linked_list_assert_index(list, new_index);
		// get nodes
		node* prev_node = _linked_list_get_node_at(list, new_index);
		node* after_node = prev_node->next;
		node* new_node = _linked_list_new_node();
		new_node->value = value;
		// set connections
		prev_node->next = new_node;
		new_node->next = after_node;
	}

	// increment list length
	list->length++;
}

// append value
void linked_list_append_value(linked_list *list, void* value)
{
	// add to empty list
	if (list->length == 0)
	{
		list->head = _linked_list_new_node();
		list->head->value = value;
	}
	// add to tail of the list
	else
	{
		node *tail = _linked_list_get_node_at(list, list->length - 1);
		tail->next = _linked_list_new_node();
		tail->next->value = value;
	}

	// increment list length
	list->length++;
}

// remove value at index
void* linked_list_remove_value_at(linked_list *list, int index)
{
	_linked_list_assert_index(list, index);
}

// remove value
int linked_list_remove_value(linked_list *list, void* value)
{
	return 0;
}

