#include "Node.h"
#include <iostream>
Node::Node(char *id)
{
	
	this->id = id;
	for(int i = 0; i<16; i++) matrix[i] = 0.0;

	root = false;


	
}

char *Node::getId()
{
	return id;
}

char *Node::getParentId()
{
	return parent->getId();
}

void Node::setParent(Node *parent)
{
	this->parent = parent;
}

void Node::setChildren(vector<Node*> children)
{
	this->children = children;
}

float *Node::getMatrix()
{
	return matrix;
}

void Node::setRoot()
{
	root = true;
}

bool Node::isRoot()
{
	return root;
}
void Node::addChild(Node *child)
{
	children.push_back(child);
	child->setParent(this);
	child->setMatrix(matrix);
}

void Node::setMatrix(float mat[16])
{
	 memcpy(matrix, mat, 16*sizeof(float));
}

vector <Node *> Node::getChildren()
{
	return children;
}
/*int Node::setNextMatrixValue(float value)
{
	for(int i = 0; i< 16; i++)
	{
		if(matrix[i] == -1.0) 
			{
				matrix[i] = value;
				
				return 0;
			}
	}

	return 1;
}*/