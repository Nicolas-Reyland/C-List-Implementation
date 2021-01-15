/* LinkedList test file */
typedef char LINKED_LIST_TYPE;
#include "LinkedList.h"
//#include "CharLinkedList.h"

int main() {
	LinkedList list;
	//CharLinkedList list;
	initListAtValue(&list, 'b');

	insertValueAtIndex(&list, 'd', 1);
	insertValueAtIndex(&list, 'c', 1);
	insertValueAtIndex(&list, 'a', 0);

	//removeValueAtIndex(&list, 0);
	//removeValueAtIndex(&list, 1);

	printLinkedList(&list);

	return 0;
}
