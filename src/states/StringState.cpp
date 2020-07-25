#include "../StateDefinitions.h"

StringState::StringState(Parser* prs) : AbstractState(prs, StateName::String), inEscape(false) {}

void StringState::processChar(const char ch) {
	if (inEscape) {
		inEscape = false;
		dataDataAppend(AbstractState::escapeChar(ch));
		return;
	}
	switch (ch) {
	case '\\':
		inEscape = true;
		return;
	case '\"':
		dataLevelUp();
		deleteLater();
		popState();
		return;
	}
	dataDataAppend(ch);
}