#include "../StateDefinitions.h"

NullState::NullState(Parser* prs) : AbstractState(prs, StateName::Null), position(0) {}

void NullState::processChar(const char ch) {
	const char* nullMask = "ull"; // 'n' letter was already processed, else this state wasn't created.
	if (ch != nullMask[position++]) {
		setError("null expected");
	}
	if (position == 3) {
		parser->currentNode->data = "null";
		deleteLater();
		popState();
		dataLevelUp();
	}
}