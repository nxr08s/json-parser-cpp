#include "../StateDefinitions.h"

TrueState::TrueState(Parser* prs) : AbstractState(prs, StateName::True), position(0) {}

void TrueState::processChar(const char ch) {
	const char* trueMask = "rue"; // 'f' letter was already processed, else this state wasn't created.
	if (ch != trueMask[position++]) {
		setError("true expected");
	}
	if (position == 3) {
		parser->currentNode->data = "true";
		deleteLater();
		popState();
		dataLevelUp();
	}
}