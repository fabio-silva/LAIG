#ifndef GRAFO_H
#define GRAFO_H

#include "Node.h"

class Grafo{

public:
	Grafo();
	void insertNode(Node *n);
	vector <Node *> getTree();

protected:
	vector<Node*> tree;
};
#endif