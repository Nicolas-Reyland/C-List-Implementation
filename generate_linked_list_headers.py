#!/bin/python3
# Generate Headers for LinkedLists for various data_types (custom structs, etc.)
# data is excepted like: Int=int Float=float "Book=struct Books {char title[100]; char author[100]; int book_id;}"
# which would give the following header files: LinkedListInt.h LinkedListFloat.h LinkedListBook.h
import sys
LINE_INDEX = 7

# go to main directory
from os import chdir
from os.path import dirname, abspath, isfile
chdir(dirname(abspath(__file__)))

# change the source code of CustomLinkedList.h to the desired source code
def generate_header(name, data_type):
	file = open('_CustomLinkedList.h', 'r')
	lines = file.readlines()
	file.close()

	for i in range(len(lines)):
		if i == LINE_INDEX:
			lines[LINE_INDEX] = 'typedef {} {}_LINKED_LIST_TYPE;\n'.format(data_type, name)
			continue
		#lines[i] = lines[i].replace('__Custom__LinkedList', '{}LinkedList'.format(name))
		lines[i] = lines[i].replace('LINKED_LIST_TYPE', '{}_LINKED_LIST_TYPE'.format(name))
		#lines[i] = lines[i].replace('struct Node', 'struct {}Node'.format(name))
		lines[i] = lines[i].replace('__Custom__', name)

	filename = '{}LinkedList.h'.format(name)
	assert not isfile(filename) # the file should not already exist!
	file = open(filename, 'w')
	file.writelines(lines)
	file.close()


if __name__ == '__main__':
	# use the given args to generate headers
	for arg in sys.argv[1:]:
		name, data_type = arg.split('=')
		try:
			generate_header(name, data_type)
		except AssertionError:
			print('Generation failed for {}. File already exists'.format(name))
			continue
		print('Generated header for {0} with struct name {0}LinkedList'.format(name))

