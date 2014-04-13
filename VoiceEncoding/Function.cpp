#include "Function.h"
#include "Terminal.h"

Function::Function(FunctionType type, Function* parent)
{
	m_type = type;
	m_nodeType = Node::FunctionType;

	m_childOne = m_childTwo = 0;
}
Function::~Function()
{
	//We take ownership of all children, so delete them..
	if (m_childOne)
		delete m_childOne;
	
	if (m_childTwo)
		delete m_childTwo;
}

void Function::setChildOne(Node* child) {
	if (m_childOne)
		m_childOne->setParentNode(0);	//it loses it's parent

	m_childOne = child;
	m_childOne->setParentNode(this);
}
void Function::setChildTwo(Node* child) {
	if (m_childTwo)
		m_childTwo->setParentNode(0);

	m_childTwo = child;
	m_childTwo->setParentNode(this);
}

string Function::expression(const segmentHistory_t segmentHistory) {
	string expressionString = "";
	string childOneExpression = "";
	string childTwoExpression = "";

	//For both children: if it's a terminal, just grab it's expression string. If it's a function, we need to
	//query it for it's expression, which in turn is dependent on it's children.
	if (m_childOne->nodeType() == Node::FunctionType) {
		Function* childOne = static_cast<Function*>(m_childOne);
		childOneExpression = childOne->expression(segmentHistory);
		childOneExpression = string("(") + childOneExpression;
		childOneExpression = childOneExpression.append(")");
	} else {
		Terminal* childOne = static_cast<Terminal*>(m_childOne);
		childOneExpression = childOne->terminalString(segmentHistory);
	}

	//Same for child two;
	if (m_childTwo->nodeType() == Node::FunctionType) {
		Function* childTwo = static_cast<Function*>(m_childTwo);
		childTwoExpression = childTwo->expression(segmentHistory);
		childTwoExpression = string("(") + childTwoExpression;
		childTwoExpression = childTwoExpression.append(")");
	}
	else {
		Terminal* childTwo = static_cast<Terminal*>(m_childTwo);
		childTwoExpression = childTwo->terminalString(segmentHistory);
	}

	//Insert our operator
	string operationExpression = functionString();
	expressionString = childOneExpression + operationExpression + childTwoExpression;
	
	return expressionString;
}

vector<Node*> Function::getChildren() {
	vector<Node*> childrenList;
	childrenList.push_back(this);

	if (m_childOne) {
		if (m_childOne->nodeType() == Node::FunctionType) {
			Function *childOne = static_cast<Function*>(m_childOne);
			vector<Node*> childOneChildren = childOne->getChildren();
			childrenList.insert(childrenList.begin(), childOneChildren.begin(), childOneChildren.end());

		} else {
			childrenList.push_back(m_childOne);
		}
	}

	if (m_childTwo) {
		if (m_childTwo->nodeType() == Node::FunctionType) {
			Function *childTwo = static_cast<Function*>(m_childTwo);
			vector<Node*> childTwoChildren = childTwo->getChildren();
			childrenList.insert(childrenList.begin(), childTwoChildren.begin(), childTwoChildren.end());
		} else {
			childrenList.push_back(m_childTwo);
		}
	}

	return childrenList;
}

string Function::functionString() {
	switch (m_type) {
	case Add:
		return "+";
	case Subtract:
		return "-";
	case Multiply:
		return "*";
	case Divide:
		return "/";
	case Min:
		return "min";
	case Max:
		return "max";
	default:
		return "(ERROR)";
	}
}

Function::OperationFunction Function::functionPointer() {
	switch (m_type) {
	case Add:
		return &Node::add;
	case Subtract:
		return &Node::sub;
	case Multiply:
		return &Node::mul;
	case Divide:
		return &Node::div;
	case Min:
		return &Node::min;
	case Max:
		return &Node::max;
	default:
		return &Node::identity;
	}
}

Function* Function::deepCopy(Function* parent) {
	Function* root = new Function(functionType(), parent);

	if (m_childOne) {
		if (m_childOne->nodeType() == Node::FunctionType)
			root->setChildOne(((Function*)m_childOne)->deepCopy(root));
		else
			Terminal* childOneCopy = new Terminal(static_cast<Terminal*>(m_childOne)->terminalType(), root);
	}

	if (m_childTwo) {
		if (m_childTwo->nodeType() == Node::FunctionType)
			root->setChildTwo(((Function*)m_childTwo)->deepCopy(root));
		else
			Terminal* childTwoCopy = new Terminal(static_cast<Terminal*>(m_childTwo)->terminalType(), root);
	}

	return root;
}

int Function::compute(const segmentHistory_t segmentHistory) {
	int childOneCalculation, childTwoCalculation;
	Function::OperationFunction opFunc = functionPointer();

	if (m_childOne->nodeType() == Node::FunctionType)
		childOneCalculation = static_cast<Function*>(m_childOne)->compute(segmentHistory);
	else
		childOneCalculation = static_cast<Terminal*>(m_childOne)->terminalInt(segmentHistory);


	if (m_childTwo->nodeType() == Node::FunctionType)
		childTwoCalculation = static_cast<Function*>(m_childTwo)->compute(segmentHistory);
	else
		childTwoCalculation = static_cast<Terminal*>(m_childTwo)->terminalInt(segmentHistory);

	return (*opFunc)(childOneCalculation, childTwoCalculation);
}

string Function::expression() {
	string expressionString = "";
	string childOneExpression = "";
	string childTwoExpression = "";

	if (m_childOne->nodeType() == Node::FunctionType) {   //this child is a function, recurse and get this function's exp str
		Function* childOne = static_cast<Function*>(m_childOne);
		childOneExpression = childOne->expression();
		childOneExpression = "(" + childOneExpression;
		childOneExpression = childOneExpression.append(")");
	}
	else {
		Terminal* childOne = static_cast<Terminal*>(m_childOne);
		childOneExpression = childOne->terminalString();
	}

	//now get the expression for child two
	if (m_childTwo->nodeType() == Node::FunctionType) {
		Function* childTwo = static_cast<Function*>(m_childTwo);
		childTwoExpression = childTwo->expression();
		childTwoExpression = "(" + childTwoExpression;
		childTwoExpression = childTwoExpression.append(")");
	}
	else {
		Terminal* childTwo = static_cast<Terminal*>(m_childTwo);
		childTwoExpression = childTwo->terminalString();
	}

	//got the expressions for both children. Now, we need to insert our function operator between the two children

	string operationExpression = functionString();
	expressionString = childOneExpression + operationExpression + childTwoExpression;

	return expressionString;
}

vector<Node*> Function::preOrder(vector<Node*> children, int startingId) {

	setId(startingId++);
	children.push_back(this);

	if (m_childOne->nodeType() == Node::FunctionType) {
		Function *childOne = static_cast<Function*>(m_childOne);
		vector<Node*> childOnePreOrder = childOne->preOrder(vector<Node*>(), startingId);
		children.insert(children.end(), childOnePreOrder.begin(), childOnePreOrder.end());
	}
	else {
		Terminal* childOne = static_cast<Terminal*>(m_childOne);
		childOne->setId(startingId++);
		children.push_back(childOne);
	}

	//update the starting id to reflect changes from the left branching side
	startingId = children.back()->id() + 1;


	if (m_childTwo->nodeType() == Node::FunctionType) {
		Function *childTwo = static_cast<Function*>(m_childTwo);
		vector<Node*> childTwoPreOrder = childTwo->preOrder(vector<Node*>(), startingId);
		children.insert(children.end(), childTwoPreOrder.begin(), childTwoPreOrder.end());
	}
	else {
		Terminal* childTwo = static_cast<Terminal*>(m_childTwo);
		childTwo->setId(startingId++);
		children.push_back(childTwo);
	}


	return children;
}