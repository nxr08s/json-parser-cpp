#include "../StateDefinitions.h"

NumberState::NumberState(Parser* prs) : AbstractState(prs, StateName::Number) {}

void NumberState::processChar(const char ch) {
	if (isdigit(ch) || ch == '.' || ch == '+' || ch == '-') {
		dataDataAppend(ch);
		return;
	}
	if (isspace(ch)) {
		deleteLater();
		NEWSTATE(AfterValueState);
		return;
	}
	switch (ch) {
	case ']':
	case '}':
		dataLevelUp();
		dataLevelUp();
		deleteLater();
		doublePopState();
		break;
	case ',':
		dataLevelUp();
		deleteLater();
		popState();
		break;
	default:
		setError("another value expected");
	}
}