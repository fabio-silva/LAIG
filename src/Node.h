#ifndef NODE_H
#define NODE_H

#include "CGFappearance.h"
#include "Material.h"
#include <vector>
#include <string>
#include "Primitiva.h"
using namespace std;


class Node
{
public:
	Node(char *id, bool root);
	char* getId();
	char* getParentId();
	void setParent(Node *parent);
	void setChildren(vector<Node*> children);
	float* getMatrix();
	void addChild(Node *child);
	bool isRoot();
	vector<Node *> getChildren();
	void setMatrix(float mat[16]);
	void setMaterial(Material *m);
	Material *getMaterial();
	void addPrimitiva(Primitiva *p); 
	vector<float> getData();
	char* getCullOrder();
	Node *getParent();
	vector<Primitiva *> getPrimitivas();

protected:
	float preMatrix[16];
	float Matrix[16];
	vector <Node*> children; 
	Node *parent;
	char *id;
	bool root;
	Material *material;
	vector<Primitiva *> primitivas;
	char *cullorder;
	vector<float> data;
};

#endif