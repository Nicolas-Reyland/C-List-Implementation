/* StaticList test file */
typedef int STATIC_LIST_TYPE;
#include "StaticList.h" // this works too
//#include "IntStaticList.h"

int main() {
	StaticList list;
	//IntStaticList list;
	int values[] = {1, 2, 3};
	initListAtValues(&list, 3, values);
	printList(&list);

	return 0;
}
