#include "../StateDefinitions.h"

AfterNameState::AfterNameState(Parser* prs) : AbstractState(prs, StateName::AfterName) {}

void AfterNameState::processChar(const char ch) {
	if (isspace(ch)) return;
	if (ch == ':') {
		NEWSTATE(BeforeValueState);
		deleteLater();
		return;
	}
	setError("':' after name expected");
}