#include "Terminal.h"


Terminal::Terminal(TerminalType type, Function* parent)
{
	m_type = type;
	m_nodeType = Node::TerminalType;
}

string Terminal::terminalString(const segmentHistory_t segmentHistory) {
	// P_1, P_2, P_5, P_10, One, Two, Ten
	switch (m_type) {
	case P_1:
		return to_string(segmentHistory.p1);
	case P_2:
		return to_string(segmentHistory.p2);
	case P_5:
		return to_string(segmentHistory.p5);
	case P_10:
		return to_string(segmentHistory.p10);
	case One:
		return string("1");
	case Two:
		return string("2");
	case Ten:
		return string("10");
	default:
		return string("(ERROR)");
	}
}

string Terminal::terminalString() {
	switch (m_type) {
	case P_1:
		return string("P1");
	case P_2:
		return string("P2");
	case P_5:
		return string("P5");
	case P_10:
		return string("P10");
	case One:
		return string("1");
	case Two:
		return string("2");
	case Ten:
		return string("10");
	default:
		return string("(ERROR)");
	}
}

int Terminal::terminalInt(const segmentHistory_t segmentHistory) {
	switch (m_type) {
	case P_1:
		return segmentHistory.p1;
	case P_2:
		return segmentHistory.p2;
	case P_5:
		return segmentHistory.p5;
	case P_10:
		return segmentHistory.p10;
	case One:
		return 1;
	case Two:
		return 2;
	case Ten:
		return 10;
	default:
		return 0;
	}
}