#include "../StateDefinitions.h"

FalseState::FalseState(Parser* prs) : AbstractState(prs, StateName::False), position(0) {}

void FalseState::processChar(const char ch) {
	const char* falseMask = "alse"; // 'f' letter was already processed, else this state wasn't created.
	if (ch != falseMask[position++]) {
		setError("false expected");
	}
	if (position == 4) {
		parser->currentNode->data = "false";
		deleteLater();
		popState();
		dataLevelUp();
	}
}