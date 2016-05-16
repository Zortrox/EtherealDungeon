#pragma once

#ifndef _Potion_included_
#define _Potion_included_

#include "Consumable.h"

class Potion: public Consumable {
public:
	Potion();
	virtual ~Potion();
	virtual bool use(Creature &playerRef, std::string &strMessage);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual Potion* clone();

	//getters & setters

protected:

private:

};

#endif