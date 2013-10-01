#include "Node.h"
#include <iostream>
#include "CGFapplication.h"


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


void Node::setTextureFile(char *path)
{
	string _path(path);
	textura = new CGFappearance(_path,GL_REPEAT,GL_REPEAT);
}