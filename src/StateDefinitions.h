#pragma once

#include "Parser.h"
#include "DataTree.h"

#define NEWSTATE(x) parser->currentState = (AbstractState*)(new x(parser))

enum class StateName {
	Initial,
	Object,
	Array,
	Name,
	AfterName,
	BeforeValue,
	Number,
	String,
	AfterValue,
	Escape,
	True,
	False,
	Null
};

class Parser;

#ifdef _DEBUG
static unsigned int objectsCount;
#endif // _DEBUG

class AbstractState {
protected:
	static const char escapeChar(const char ch);

	StateName name;
	Parser* parser;

	AbstractState(Parser*, const StateName);
	void deleteLater();
	void pushThis();
	void popState();
	void doublePopState();
	void setError(const char*);
	void newNode(DataTree::DataType);

	void dataLevelUp() const;
	void dataNameAppend(const char) const;
	void dataDataAppend(const char) const;

public:
	StateName getStateName() const;
	virtual void processChar(const char ch) = 0;

#ifdef _DEBUG
	void* operator new(size_t size);
	void operator delete(void* ptr);
#endif // _DEBUG
};

class ObjectState : public AbstractState {
public:
	ObjectState(Parser* parser);
	void processChar(const char ch) final;
};

class NameState : public AbstractState {
	bool inEscape;
public:
	NameState(Parser* prs);
	void processChar(const char ch) final;
};

class InitialState : public AbstractState {
public:
	InitialState(Parser* parser);
	void processChar(const char ch) final;
};

class ArrayState : public AbstractState {
public:
	ArrayState(Parser* parser);
	void processChar(const char ch) final;
};

class BeforeValueState : public AbstractState {
public:
	BeforeValueState(Parser*);
	void processChar(const char ch) final;
};

class NumberState : public AbstractState {
public:
	NumberState(Parser*);
	void processChar(const char ch) final;
};

class StringState : public AbstractState {
	bool inEscape;
public:
	StringState(Parser*);
	void processChar(const char ch) final;
};

class AfterValueState : public AbstractState {
public:
	AfterValueState(Parser*);
	void processChar(const char ch) final;
};

class TrueState : public AbstractState {
	unsigned int position;
public:
	TrueState(Parser*);
	void processChar(const char ch) final;
};

class FalseState : public AbstractState {
	unsigned int position;
public:
	FalseState(Parser*);
	void processChar(const char ch);
};

class NullState : public AbstractState {
	unsigned int position;
public:
	NullState(Parser*);
	void processChar(const char ch) final;
};

class AfterNameState : public AbstractState {
public:
	AfterNameState(Parser*);
	void processChar(const char ch) final;
};
