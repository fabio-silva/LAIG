#include "Node.h"
#include <iostream>
#include "CGFapplication.h"


Node::Node(char *id, bool root)
{		
	this->id = id;
	material = NULL;	
	this->root = root;
	parent = NULL;
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, Matrix);
	usingDisplayList = false;
	listId = -1;
}

char *Node::getId()
{
	return id;
}

char *Node::getParentId()
{
	if(parent == NULL) return NULL;
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
	return Matrix;
}

bool Node::isRoot()
{
	return root;
}
void Node::addChild(Node *child)
{
	children.push_back(child);
	child->setParent(this);
}

void Node::setMatrix(float mat[16])
{
	memcpy(Matrix, mat, 16*sizeof(float));
}

vector <Node *> Node::getChildren()
{
	return children;
}

void Node::setMaterial(Material *m)
{
	material = m;
}

void Node::addPrimitiva(Primitiva *p)
{
	primitivas.push_back(p);
}

vector<float> Node::getData()
{
	return data;
}

char *Node::getCullOrder()
{
	return cullorder;
}

Node * Node::getParent()
{
	return parent;
}

vector<Primitiva *> Node::getPrimitivas()
{
	return primitivas;
}

Material *Node::getMaterial()
{
	return material;
}

void Node::useDisplayList(bool d)
{
	usingDisplayList = d;
}

bool Node::isUsingDisplayList()
{
	return usingDisplayList;
}

void Node::setListId(int id)
{
	this->listId = id;
}

int Node::getListId()
{
	return listId;
}