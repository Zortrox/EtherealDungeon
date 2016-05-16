#pragma once

#ifndef _Armor_included_
#define _Armor_included_

#include "Item.h"

class Armor: public Item {
public:
	Armor();
	virtual ~Armor();
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual Armor* clone();
	virtual bool equip(Creature &playerRef);

	//getters & setters
	virtual std::string getSlot();
	virtual void setSlot(std::string strSlot);
	virtual std::string getType();
	virtual void setType(std::string strType);
	virtual int getArmorType();
	virtual void setArmorType(int intArmorType);
protected:

private:
	std::string m_strSlot;
	std::string m_strType;
	int m_intArmorType;
};

#endif