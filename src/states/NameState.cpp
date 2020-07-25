#include "../StateDefinitions.h"

NameState::NameState(Parser* prs) : AbstractState(prs, StateName::Name), inEscape(false) {}

void NameState::processChar(const char ch) {
	if (inEscape) {
		inEscape = false;
		dataNameAppend(AbstractState::escapeChar(ch));
		return;
	}
	switch (ch) {
	case '\\':
		inEscape = true;
		return;
	case '\"':
		NEWSTATE(AfterNameState);
		deleteLater();
		return;
	}
	dataNameAppend(ch);
}