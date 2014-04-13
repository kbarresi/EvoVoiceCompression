#pragma once
#include "Node.h"

#include <string>
#include <vector>

using namespace std;

class Function :
	public Node
{
public:
	enum FunctionType { Add, Subtract, Multiply, Divide, Min, Max };
	typedef int(*OperationFunction)(const int, const int);

	Function(FunctionType type, Function* parent = 0);
	~Function();


	vector<Node*> getChildren();

	//NOTE: Setting childen gives the parent ownership. i.e the parent deletes them...
	void setChildOne(Node* child);
	void setChildTwo(Node* child);
	void setChildren(Node* childOne, Node* childTwo) { setChildOne(childOne); setChildTwo(childTwo); }

	Node* childOne() { return m_childOne; }
	Node* childTwo() { return m_childTwo; }

	void setType(FunctionType type) { m_type = type; }
	FunctionType functionType() { return m_type; }

	string expression(const segmentHistory_t segmentHistory);
	string expression();

	string functionString();
	OperationFunction functionPointer();

	Function* deepCopy(Function* parent);
	int compute(const segmentHistory_t segmentHistory);

	vector<Node*> preOrder(vector<Node*> children = vector<Node*>(), int startingId = 0);

private:
	FunctionType m_type;

	Node*  m_childOne;
	Node* m_childTwo;
};

