/* StaticList Struct */
#include <stdio.h> // temorary, just for debugging
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// YOU NEED TO typedef THE STATIC_LIST_TYPE YOU WANT TO USE FOR THIS StaticList
// Look at LinkedList.h if you need more details on STATIC_LIST_TYPE (and how to use it in practice)

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

typedef struct StaticLists {
	int num_elements;
	size_t size;
	STATIC_LIST_TYPE *array;
} StaticList;

void _checkIndex(StaticList *list, int index) {
	if (index > list->num_elements) {
		fprintf(stderr, "Index out of bounds. Exiting\n");
		exit(EXIT_FAILURE);
	}
}

void _checkAlloc(StaticList *list) {
	if (list->array == NULL) {
		fprintf(stderr, "Memory allocation failed. Exiting\n");
		exit(EXIT_FAILURE);
	}
}

void _tryRealloc(StaticList *list, int num_elements) {
	list->num_elements += num_elements;
	int new_size = list->num_elements * list->size;
	list->array = realloc(list->array, new_size);
	_checkAlloc(list);
}

void initList(StaticList *list, int num_elements) {
	list->num_elements = num_elements;
	list->size = sizeof(STATIC_LIST_TYPE);
	list->array = calloc(num_elements, list->size);

	_checkAlloc(list);
}

void initListAtValue(StaticList *list, STATIC_LIST_TYPE value) {
	initList(list, 1);
	*(list->array) = value;
}

void initListAtValues(StaticList *list, int num_elements, STATIC_LIST_TYPE values[]) {
	initList(list, num_elements);
	for (register int i = 0; i < num_elements; i++) {
		*(list->array + i) = values[i];
	}
}

void insertValueAtIndex(StaticList *list, STATIC_LIST_TYPE element, int index) {
	_checkIndex(list, index);
	_tryRealloc(list, 1);
	for (register int i = list->num_elements; i > index; i--) {
		*(list->array + i) = *(list->array + i - 1);
	}
	*(list->array + index) = element;
}

STATIC_LIST_TYPE getValueAtIndex(StaticList *list, int index) {
	_checkIndex(list, index);
	STATIC_LIST_TYPE element = *(list->array + index);
	return element;
}

STATIC_LIST_TYPE removeValueAtIndex(StaticList *list, int index) {
	_checkIndex(list, index);
	STATIC_LIST_TYPE removed = *(list->array + index);
	for (register int i = index; i < list->num_elements - 1; i++) {
		*(list->array + i) = *(list->array + i + 1);
	}
	_tryRealloc(list, -1);
	return removed;
}

void addValueAtEnd(StaticList *list, STATIC_LIST_TYPE element) {
	_tryRealloc(list, 1);
	*(list->array + list->num_elements - 1) = element; // num_elements already increased
}

void addValuesAtEnd(StaticList *list, STATIC_LIST_TYPE elements[], int num_elements) {
	int start_index = list->num_elements;
	_tryRealloc(list, num_elements);
	for (register int i = 0; i < num_elements; i++) {
		*(list->array + start_index + i) = elements[i];
	}
}

void newValueAtIndex(StaticList *list, STATIC_LIST_TYPE element, int index) {
	_checkIndex(list, index);
	*(list->array + index) = element;
}

/*_Bool valueInList(StaticList *list, STATIC_LIST_TYPE element) {
	for (int i = 0; i < list->num_elements; i++) {
		if (memcmp((list->array + i), &element, list->size)) {
			return 1;
		}
	}
	return 0;
}*/

/* If the value is not in the list, return -1 */
/*int indexOfValue(StaticList *list, STATIC_LIST_TYPE element, int start_index) {
	_checkIndex(list, start_index);
	for (int i = start_index; i < list->num_elements; i++) {
		if (memcmp((list->array + i), &element, list->size)) {
			return i;
		}
	}
	return -1;
}*/

void printList(StaticList *list) {
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

	// declare a varaible with type STATIC_LIST_TYPE
	STATIC_LIST_TYPE elem;

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
	for (int i = 0; i < list->num_elements; i++) {
		printf(str, i, *(list->array + i));
	}
}
