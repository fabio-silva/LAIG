#ifndef NODE_H
#define NODE_H

#include <vector>

using namespace std;

class Node
{
public:
	Node(char *id);
	char *getId();
	char *getParentId();
	void setParent(Node *parent);
	void setChildren(vector<Node*> children);
	float *getMatrix();
	void addChild(Node *child);
	//int setNextMatrixValue (float value);

protected:
	float matrix[16];
	vector <Node*> children; 
	Node *parent;
	char *id;
};

#endif