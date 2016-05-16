#pragma once

#ifndef _Ammunition_included_
#define _Ammunition_included_

#include "Item.h"

class Ammunition: public Item {
public:
	Ammunition();
	virtual ~Ammunition();
	virtual void memberName();
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual Ammunition* clone();
	virtual bool equip(Creature &playerRef);

	//getters & setters
	virtual void setDamageBonus(int intDamageBonus);
	virtual int getDamageBonus();
	virtual void setType(std::string strType);
	virtual std::string getType();
protected:

private:
	int m_intDamageBonus;
	std::string m_strType;
};

#endif