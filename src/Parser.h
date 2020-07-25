#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "StateDefinitions.h"
#include "DataTree.h"

class AbstractState;

class Parser {
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

	AbstractState* currentState;
	AbstractState* stateToDelete;

	DataTree* root;
	DataTree* currentNode;

	bool isError;
	bool isDone;
	bool toDelete;

	std::stack<AbstractState*> stack;
	std::string errorMessage;

	const char* jsonSource;
	const int jsonLength;

	unsigned int position;

	static const char* StateStrings[];

public:
	Parser(const char*, const size_t = 0);
	~Parser();

	bool parse(const bool autoparse = true);
	const DataTree* getData() const;
	const char* getError() const;
	const char* getState() const;
	const bool success() const;
	const unsigned int getPos() const;
	const std::stack<AbstractState*>* getStack() const;

};

