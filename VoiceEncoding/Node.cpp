#include "Node.h"
#include "Function.h"
#include "Terminal.h"

Node::Node(Function* parent)
{
	m_parent = parent;

	if (parent) {
		if (!parent->childOne())
			parent->setChildOne(this);
		else
			parent->setChildTwo(this);
	}

	m_id = 0;
}

