#include "../StateDefinitions.h"

BeforeValueState::BeforeValueState(Parser* prs) : AbstractState(prs, StateName::BeforeValue) {}

void BeforeValueState::processChar(const char ch) {
	if (isspace(ch)) return;
	if (isdigit(ch) || ch == '.' || ch == '+' || ch == '-') {
		NEWSTATE(NumberState);
		parser->currentNode->type = DataTree::DataType::Number;
		dataDataAppend(ch);
	}
	else {
		switch (tolower(ch)) {
		case '\"':
			NEWSTATE(StringState);
			parser->currentNode->type = DataTree::DataType::String;
			break;
		case '{':
			NEWSTATE(ObjectState);
			parser->currentNode->type = DataTree::DataType::Object;
			break;
		case '[':
			NEWSTATE(ArrayState);
			parser->currentNode->type = DataTree::DataType::Array;
			break;
		case 't':
			NEWSTATE(TrueState);
			parser->currentNode->type = DataTree::DataType::Bool;
			break;
		case 'f':
			NEWSTATE(FalseState);
			parser->currentNode->type = DataTree::DataType::Bool;
			break;
		case 'n':
			NEWSTATE(NullState);
			parser->currentNode->type = DataTree::DataType::Null;
			break;
		default:
			setError("value after ':' expected");
		}
	}
	deleteLater();
}