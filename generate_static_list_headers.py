#!/bin/python3
# Generate Headers for StaticLists for various data_types (custom structs, etc.)
# data is excepted like: Int=int Float=float "Book=struct Books {char title[100]; char author[100]; int book_id;}"
# which would give the following header files: StaticListInt.h StaticListFloat.h StaticListBook.h
import sys
LINE_INDEX = 7

# go to main directory
from os import chdir
from os.path import dirname, abspath, isfile
chdir(dirname(abspath(__file__)))

# change the source code of CustomStaticList.h to the desired source code
def generate_header(name, data_type):
	file = open('_CustomStaticList.h', 'r')
	lines = file.readlines()
	file.close()

	for i in range(len(lines)):
		if i == LINE_INDEX:
			lines[LINE_INDEX] = 'typedef {} {}_STATIC_LIST_TYPE;\n'.format(data_type, name)
			continue
		lines[i] = lines[i].replace('__Custom__StaticList', '{}StaticList'.format(name))
		lines[i] = lines[i].replace('STATIC_LIST_TYPE', '{}_STATIC_LIST_TYPE'.format(name))

	filename = '{}StaticList.h'.format(name)
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
		print('Generated header for {0} with struct name {0}StaticList'.format(name))

