#include "Grafo.h"

Grafo::Grafo()
{
}

void Grafo::insertNode(Node *n)
{
	if(tree.empty()) n->setRoot();
	
	tree.push_back(n);
}

vector<Node *> Grafo::getTree()
{
	return tree;
}
