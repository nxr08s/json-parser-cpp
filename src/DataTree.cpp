#include "DataTree.h"

const char* DataTree::dataTypeStrings[] = {
	"Объект",
	"Массив",
	"Число",
	"Строка",
	"Логический",
	"Null"
};

#ifdef _DEBUG
unsigned int DataTree::counter;

void* DataTree::operator new(const size_t size) {
	counter++;
	return malloc(size);
}

void DataTree::operator delete(void* ptr) {
	counter--;
	free(ptr);
	std::cout << "DEBUG: total number of DATATREE objects: " << counter << std::endl;
}
#endif // _DEBUG


DataTree::DataTree() {};

DataTree::~DataTree() {
	for (DataTree* node : children)
		delete node;
}

const char* DataTree::getName() const { return name.c_str(); }

const char* DataTree::getData() const { return data.c_str(); }

const DataTree::DataType DataTree::getType() const { return type; }

const std::vector<DataTree*>* DataTree::getChildren() const { return &children; }