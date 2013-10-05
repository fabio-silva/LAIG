#include "Node.h"
#include <iostream>
#include "CGFapplication.h"


Node::Node(char *id, bool root)
{
	
	this->id = id;
	for(int i = 0; i<16; i++) matrix[i] = 0.0;

	this->root = root;
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

bool Node::isRoot()
{
	return root;
}
void Node::addChild(Node *child)
{
	children.push_back(child);
	child->setParent(this);
	child->setMatrix(matrix);
	child->setMaterial(material);
}

void Node::setMatrix(float mat[16])
{
	 memcpy(matrix, mat, 16*sizeof(float));
}

vector <Node *> Node::getChildren()
{
	return children;
}

void Node::setMaterial(Material *m)
{
	
	this->material = m;
}

void Node::setPrimitiva(char *primitiva, vector<float> data, char *cullorder)
{

	this->primitiva = primitiva;
	this->data = data;
	this->cullorder = cullorder;
}

vector<float> Node::getData()
{
	return data;
}

char *Node::getTipo()
{
	return primitiva;
}

char *Node::getCullOrder()
{
	return cullorder;
}

void Node::translate(float m[16])
{
	glLoadMatrixf(matrix);
	glMultMatrixf(m);
}

void Node::rotate(float m[16])
{
	glLoadMatrixf(matrix);
	glMultMatrixf(m);
}

void Node::scale(float m[16])
{
	glLoadMatrixf(matrix);
	glMultMatrixf(m);
}