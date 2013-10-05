#ifndef NODE_H
#define NODE_H

#include "CGFappearance.h"
#include "Material.h"
#include <vector>
#include <string>
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
	void setPrimitiva(char *tipo, vector<float> data, char *cullorder); 
	vector<float> getData();
	char* getTipo();
	char* getCullOrder();
	void translate(float m[16]);
	void rotate(float m[16]);
	void scale(float m[16]);

protected:
	float matrix[16];
	vector <Node*> children; 
	Node *parent;
	char *id;
	bool root;
	Material *material;
	char *primitiva;
	char *cullorder;
	vector<float> data;
};

#endif