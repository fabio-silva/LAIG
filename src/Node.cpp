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


	/*glPushMatrix();
	glLoadMatrixf(Matrix);
	glMultMatrixf(parent->getMatrix());
	glGetFloatv(GL_MODELVIEW_MATRIX, Matrix);
	glPopMatrix();*/
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
	if(child->getMaterial() == NULL && child->getPrimitivas().size()!=0) 
		{
			child->setMaterial(material);
			if(material != NULL )cout << "No " << child->getId() << " a herdar textura: " << material->getTexture()->getFilePath() << endl;
			//if(material->getId() == NULL) cout << "
	}
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
	if(m != NULL) 
		{
		/*	cout << "No : " << id << ", material = " << m->getTexture()->getFilePath() << endl;
			getchar();*/
			
	}
	material = m;
}

void Node::addPrimitiva(Primitiva *p)
{
	/*cout << "No: " << id << " " ;
	p->printTipo();
	cout << endl;*/
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
	//if(material == NULL) cout <<"nulo" <<endl;
	return material;
	
}