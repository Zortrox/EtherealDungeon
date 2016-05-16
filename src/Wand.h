#pragma once

#ifndef _Wand_included_
#define _Wand_included_

#include "Weapon.h"

class Wand: public Weapon {
public:
	Wand();
	virtual ~Wand();
	virtual void use();
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual Wand* clone();
	virtual bool equip(Creature &playerRef);

	//getters & setters

protected:

private:

};

#endif