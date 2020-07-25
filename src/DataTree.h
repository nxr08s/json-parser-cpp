#pragma once

#include <string>
#include <vector>
#include <iostream>

class DataTree {

	friend class AbstractState;
	friend class InitialState;
	friend class AfterNameState;
	friend class AfterValueState;
	friend class ArrayState;
	friend class BeforeValueState;
	friend class FalseState;
	friend class NameState;
	friend class NullState;
	friend class NumberState;
	friend class ObjectState;
	friend class StringState;
	friend class TrueState;

public:
	static const char* dataTypeStrings[];
	enum class DataType { Object, Array, Number, String, Bool, Null };

	DataTree();
	~DataTree();
private:


	DataTree* parent;
	DataType type;

	std::string name;
	std::string data;

	std::vector<DataTree*> children;

public:
	const char* getName() const;
	const char* getData() const;
	const DataType getType() const;
	const std::vector<DataTree*>* getChildren() const;

#ifdef  _DEBUG
private:
	static unsigned int counter;
public:
	void* operator new(const size_t);
	void operator delete(void*);
#endif //  _DEBUG

};