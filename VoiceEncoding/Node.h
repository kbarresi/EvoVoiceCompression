#pragma once

#include <algorithm>

class Function;
class Terminal;
class Node
{
public:
	enum NodeType { FunctionType, TerminalType };
	typedef struct {
		int p1;
		int p2;
		int p5;
		int p10;
	} segmentHistory_t;

	Node(Function* parent = 0);

	void setParentNode(Function* parentNode) { m_parent = parentNode; }
	Function *parentNode() { return m_parent; }

	NodeType nodeType() { return m_nodeType; }

	static int add(const int a, const int b) { return a + b; }
	static int sub(const int a, const int b) { return a - b; }
	static int mul(const int a, const int b) { return a * b; }
	static int div(const int a, const int b) { return a /  std::max(b, 1); } //prevents divide by 1 errors
	static int min(const int a, const int b) { return std::min(a, b); }
	static int max(const int a, const int b) { return std::min(a, b); }
	static int identity(const int a, const int b) { return a; }

	void setId(int id) { m_id = id; }
	int id() { return m_id; }

protected:
	NodeType m_nodeType;
	Function* m_parent;

private:
	int m_id;
};

