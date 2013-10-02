#include "Grafo.h"

Grafo::Grafo()
{
}

void Grafo::insertNode(Node *n)
{
	
	
	tree.push_back(n);
}

vector<Node *> Grafo::getTree()
{
	return tree;
}
