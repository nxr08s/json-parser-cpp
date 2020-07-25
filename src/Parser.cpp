#include "Parser.h"

const char* Parser::StateStrings[] = {
	"Начальное",
	"Объект",
	"Массив",
	"Имя",
	"После имени",
	"Перед значением",
	"Число",
	"Строка",
	"После значения",
	"Экранирование",
	"True",
	"False",
	"Null"
};



bool Parser::parse(const bool autoparse) {
	if (isDone || isError) return false;
	if (autoparse) {
		while ((position != jsonLength) && (jsonSource[position] != '\0')) {
			currentState->processChar(jsonSource[position]);
			if (isError)
				return false;
			if (toDelete) {
				delete stateToDelete;
				toDelete = false;
			}
			position++;
		}
		if (currentState->getStateName() == StateName::Initial) {
			isDone = true;
			return false;
		}
		else {
			isError = true;
			errorMessage = "unexpected end of file";
			return false;
		}
	}
	else {
		if ((position == jsonLength) || (jsonSource[position] == '\0')) {
			if (currentState->getStateName() == StateName::Initial) {
				isDone = true;
				return false;
			}
			else {
				isError = true;
				errorMessage = "unexpected end of file";
				return false;
			}
		}
		currentState->processChar(jsonSource[position]);
		if (toDelete) {
			delete stateToDelete;
			toDelete = false;
		}
		if (!isError)
			position++;
		return !isError;
	}
}

Parser::Parser(const char* src, const size_t length) :
	toDelete(false),
	isError(false),
	currentState((AbstractState*)(new InitialState(this))),
	stateToDelete(nullptr),
	currentNode(nullptr),
	jsonSource(src),
	jsonLength((length) ? length : -1),
	position(0)
{}

Parser::~Parser() {
	while (!stack.empty()) {
		delete stack.top();
		stack.pop();
	}
	delete root;
	delete currentState;
}

const char* Parser::getState() const { return StateStrings[(unsigned int)currentState->getStateName()]; }

const std::stack<AbstractState*>* Parser::getStack() const { return &stack; }

const char* Parser::getError() const { return errorMessage.c_str(); }

const bool Parser::success() const { return !isError; }

const DataTree* Parser::getData() const { return root; }

const unsigned int Parser::getPos() const { return position; }
