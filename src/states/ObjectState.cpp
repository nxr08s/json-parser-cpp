#include "../StateDefinitions.h"

ObjectState::ObjectState(Parser* prs) : AbstractState(prs, StateName::Object) {}

void ObjectState::processChar(const char ch) {
	if (isspace(ch) || ch == ',') return;
	switch (ch) {
	case '\"':
		NEWSTATE(NameState);
		newNode(DataTree::DataType::Array); // no matter what type is used(in future it will be overwritten)
		pushThis();
		break;
	case '}':
		dataLevelUp();
		deleteLater();
		popState();
		break;
	default:
		setError("variable's name expected");
	}
}