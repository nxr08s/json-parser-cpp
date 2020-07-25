#include "../StateDefinitions.h"

ArrayState::ArrayState(Parser* prs) :AbstractState(prs, StateName::Array) {}

void ArrayState::processChar(const char ch) {
	if (isspace(ch) || ch == ',') return;
	if (isdigit(ch) || ch == '.' || ch == '+' || ch == '-') {
		NEWSTATE(NumberState);
		newNode(DataTree::DataType::Number);
		dataDataAppend(ch);
	}
	else {
		switch (ch) {
		case '\"':
			NEWSTATE(StringState);
			newNode(DataTree::DataType::String);
			break;
		case 't':
			NEWSTATE(TrueState);
			newNode(DataTree::DataType::Bool);
			break;;
		case 'f':
			NEWSTATE(FalseState);
			newNode(DataTree::DataType::Bool);
			break;
		case 'n':
			NEWSTATE(NullState);
			newNode(DataTree::DataType::Null);
			break;
		case '{':
			NEWSTATE(ObjectState);
			newNode(DataTree::DataType::Object);
			break;
		case '[':
			NEWSTATE(ArrayState);
			newNode(DataTree::DataType::Array);
			break;
		case ']':
			dataLevelUp();
			deleteLater();
			popState();
			return;
		default:
			setError("value, ']', or ',' expected");
			return;
		}
	}
	this->pushThis();
}