#include "../StateDefinitions.h"

InitialState::InitialState(Parser* prs) : AbstractState(prs, StateName::Initial) {}

void InitialState::processChar(const char ch) {
	if (isspace(ch)) return;
	DataTree* node;
	switch (ch) {
	case '{':
		NEWSTATE(ObjectState);
		node = new DataTree;
		node->parent = nullptr;
		node->type = DataTree::DataType::Object;
		parser->root = node;
		parser->currentNode = node;
		break;
	case '[':
		NEWSTATE(ArrayState);
		node = new DataTree;
		node->parent = nullptr;
		node->type = DataTree::DataType::Array;
		parser->root = node;
		parser->currentNode = node;
		break;
	default:
		setError("'{' or '[' expected at the beginning");
		return;
	}
	pushThis();
}