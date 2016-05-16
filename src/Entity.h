#pragma once

#ifndef _Entity_included_
#define _Entity_included_

#include <string>
#include <vector>
#include "XMLSerializable.h"

class Entity: public XMLSerializable{
public:
	Entity();
	virtual ~Entity();
	virtual bool hasProperty(std::string strProp);
	virtual std::string getDescription();

	//member variables to console
	virtual void dumpObject();
	virtual void dumpObjectData();
	//member variables to XML
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	//XML to member varibales
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual Entity* clone();

	//getters & setters
	virtual std::string getName();
	virtual void setName(std::string strName);
	virtual char getDisplayChar();
	virtual void setDisplayChar(char cDisplayChar);
	virtual int getXPos();
	virtual void setXPos(int X);
	virtual int getYPos();
	virtual void setYPos(int Y);
protected:

private:
	std::string m_strName;
	std::vector<std::string> m_vecProperties;
	char m_cDisplayChar;
	int xPos;
	int yPos;
};

#endif