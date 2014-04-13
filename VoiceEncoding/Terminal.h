#pragma once
#include "Node.h"

#include <string>

using namespace std;

class Terminal :
	public Node
{
public:

	enum TerminalType { P_1, P_2, P_5, P_10, One, Two, Ten};

	Terminal(TerminalType type, Function* parent = 0);

	TerminalType terminalType() { return m_type; }
	void setType(TerminalType type) { m_type = type; }

	string terminalString(const segmentHistory_t segmentHistory);
	string terminalString();

	int terminalInt(const segmentHistory_t segmentHistory);

private:
	TerminalType m_type;
};

