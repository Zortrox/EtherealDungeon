#pragma once

#ifndef _Node_included_
#define _Node_included_

class Node{
public:
	Node();
	Node(int X, int Y);
	virtual ~Node();

	//getters & setters
	double getF();
	void setF(double F);
	double getH();
	void setH(double H);
	int getG();
	void setG(int G);

	int getX();
	void setX(int X);
	int getY();
	void setY(int Y);

	char getListType();
	void setListType(char type);

	Node* getParent();
	void setParent(Node* &Parent);
protected:

private:
	double dblF_Value;
	double dblH_Value;
	int intG_Value;

	int xPos;
	int yPos;
	
	char listType;	//X, O, C

	Node* ParentNode;
};

#endif