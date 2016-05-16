#pragma once

#ifndef _Gold_included_
#define _Gold_included_

#include "Item.h"

class Gold: public Item {
public:
	Gold();
	virtual ~Gold();
	virtual void pickUp();
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual Gold* clone();

	//getters & setters

protected:

private:

};

#endif