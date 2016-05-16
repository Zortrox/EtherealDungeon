#include "Node.h"

Node::Node()
{
	xPos = 0;
	yPos = 0;

	dblF_Value = 0;
	dblH_Value = 0;
	intG_Value = 0;

	listType = 'X';

	ParentNode = 0;
}
Node::Node(int X, int Y)
{
	xPos = X;
	yPos = Y;

	dblF_Value = 0;
	dblH_Value = 0;
	intG_Value = 0;

	listType = 'X';

	ParentNode = 0;
}
Node::~Node()
{

}

double Node::getF()
{
	return dblF_Value;
}
void Node::setF(double F)
{
	dblF_Value = F;
}
double Node::getH()
{
	return dblH_Value;
}
void Node::setH(double H)
{
	dblH_Value = H;
}
int Node::getG()
{
	return intG_Value;
}
void Node::setG(int G)
{
	intG_Value = G;
}

int Node::getX()
{
	return xPos;
}
void Node::setX(int X)
{
	xPos = X;
}
int Node::getY()
{
	return yPos;
}
void Node::setY(int Y)
{
	yPos = Y;
}

char Node::getListType()
{
	return listType;
}
void Node::setListType(char type)
{
	listType = type;
}

Node* Node::getParent()
{
	return ParentNode;
}
void Node::setParent(Node* &Parent)
{
	ParentNode = Parent;
}