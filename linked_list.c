/* LinkedList Implementation */
#include "linked_list.h"
#include <stdio.h>
#include <errno.h>

// error message
void _exit_msg(const char* msg)
{
	fprintf(stderr, msg);
	fprintf(stderr, "\n");
	exit(EXIT_FAILURE);
}

// initialize the list
void _init_list(LinkedList *list, void* value)
{
	list->length = 1;
	list->value_size = sizeof(value);
	list->head = _new_node();
	list->head->value = value;
	list->head->next = NULL;
	list->_initialized = true;
}

// is an index valid ?
bool _valid_index(LinkedList *list, int index, bool include_end)
{
	return 0 <= index && index < list->length + include_end;
}

// assert that an index is valid
void _assert_index(LinkedList *list, int index, bool include_end)
{
	if (_valid_index(list, index, include_end)) return;
	char* msg = LL_INDEX_ERROR_MSG;
	sprintf(msg, index, list->length);
	_exit_msg(msg);
}

// get the value at the index
Node* _get_node_at(LinkedList *list, int index)
{
	Node* node = list->head;

	for (int i = 0; i < index; i++)
	{
		node = node->next;
		// verify after we get the next node: the head should have been verified in the _assert_index call
		if (node == NULL)
		{
			char* msg = LL_NULL_POINTER_NODE;
			sprintf(msg, i);
			_exit_msg(msg);
		}
	}

	return node;
}

// create a new node
Node* _new_node()
{
	// allocate new memory for node
	size_t node_size = sizeof(struct Node);
	struct Node *node = (struct Node*) malloc(node_size);
	// if the pointer is NULL, the allocation faled
	if (node == NULL)
	{
		char* msg = LL_MEM_ALLOC_ERROR_MSG;
		sprintf(msg, node_size);
		_exit_msg(msg);
	}
	return node;
}


/* 'Public' Methods */

// get value at index
void* get_value_at(LinkedList *list, int index)
{
	_assert_index(list, index, false);
	return _get_node_at(list, index)->value;
}

// insert value at index
void insert_value_at(LinkedList *list, void* value, int index)
{
	// init list ?
	if (index == 0)
	{
		if (!list->_initialized)
		{
			_init_list(list, value);
			return;
		}
		// ...
	}
	_assert_index(list, index, true);
}

// remove value at index
void* remove_value_at(LinkedList *list, int index)
{
	_assert_index(list, index, false);
}

// remove value
int remove_value(LinkedList *list, void* value)
{
	return 0;
}

// append value
void append_value(LinkedList *list, void* value)
{
	// init list ?
	if (!list->_initialized)
	{
		_init_list(list, value);
		return;
	}

	// add to empty list
	if (list->length == 0)
	{
		list->head = _new_node();
		list->head->value = value;
	}
	// add to tail of the list
	else
	{
		Node *tail = _get_node_at(list, list->length - 1);
		tail->next = _new_node();
		tail->next->value = value;
	}

	list->length++;
}

