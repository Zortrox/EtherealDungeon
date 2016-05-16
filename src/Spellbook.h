#pragma once

#ifndef _Spellbook_included_
#define _Spellbook_included_

#include "Weapon.h"

class Spellbook: public Weapon {
public:
	Spellbook();
	virtual ~Spellbook();
	virtual void use();
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual Spellbook* clone();
	virtual bool equip(Creature &playerRef);

	//getters & setters

protected:

private:
	
};

#endif