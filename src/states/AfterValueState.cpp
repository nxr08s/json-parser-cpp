#include "../StateDefinitions.h"

AfterValueState::AfterValueState(Parser* prs) : AbstractState(prs, StateName::AfterValue) {}

void AfterValueState::processChar(const char ch) {
	if (isspace(ch)) return;
	switch (ch) {
	case '}':
	case ']':
		deleteLater();
		doublePopState();
		dataLevelUp();
		dataLevelUp();
		break;
	case ',':
		deleteLater();
		popState();
		dataLevelUp();
		break;
	default:
		setError("'}', ']' or ',' expected");
	}
}