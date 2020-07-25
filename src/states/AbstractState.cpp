#include "../StateDefinitions.h"

#ifdef _DEBUG
void* AbstractState::operator new(size_t size) {
	objectsCount++;
	return malloc(size);
}

void AbstractState::operator delete(void* ptr) {
	objectsCount--;
	free(ptr);
	std::cout << "DEBUG: total number of STATE objects: " << objectsCount << std::endl;
}
#endif // _DEBUG

const char AbstractState::escapeChar(const char ch) {
	char escapedChar;
	switch (ch) {
	case '"':
		escapedChar = '\"';
		break;
	case '\\':
		escapedChar = '\\';
		break;
	case '/':
		escapedChar = '/';
		break;
	case 'b':
		escapedChar = '\b';
		break;
	case 'f':
		escapedChar = '\f';
		break;
	case 'n':
		escapedChar = '\n';
		break;
	case 'r':
		escapedChar = '\r';
		break;
	case 't':
		escapedChar = '\t';
		break;
	}
	return escapedChar;
}

AbstractState::AbstractState(Parser* prs, const StateName stName) : name(stName), parser(prs) {
	parser->currentState = this;
}

void AbstractState::deleteLater() {
	parser->toDelete = true;
	parser->stateToDelete = this;
}

void AbstractState::popState() {
	parser->currentState = parser->stack.top();
	parser->stack.pop();
}

void AbstractState::doublePopState() {
	popState();
	delete parser->currentState;
	popState();
}

void AbstractState::setError(const char* errMsg) {
	parser->isError = true;
	parser->errorMessage = errMsg;
}

void AbstractState::newNode(DataTree::DataType type) {
	DataTree* node = new DataTree;
	node->parent = parser->currentNode;
	node->type = type;

	parser->currentNode->children.push_back(node);
	parser->currentNode = node;
}

void AbstractState::pushThis() { parser->stack.push(this); }

StateName AbstractState::getStateName() const { return name; }

void AbstractState::dataLevelUp() const { parser->currentNode = parser->currentNode->parent; }

void AbstractState::dataNameAppend(const char ch) const { parser->currentNode->name.push_back(ch); }

void AbstractState::dataDataAppend(const char ch) const { parser->currentNode->data.push_back(ch); }
