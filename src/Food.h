#pragma once

#ifndef _Food_included_
#define _Food_included_

#include "Consumable.h"

class Food: public Consumable {
public:
	Food();
	virtual ~Food();
	virtual bool use(Creature &playerRef, std::string &strMessage);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual Food* clone();

	//getters & setters

protected:

private:

};

#endif