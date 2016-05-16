#pragma once

#ifndef _Weapon_included_
#define _Weapon_included_

#include "Item.h"

class Weapon: public Item {
public:
	Weapon();
	virtual ~Weapon();
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual Weapon* clone();
	virtual bool equip(Creature &playerRef);

	//getters & setters
	virtual int getDamage();
	virtual void setDamage(int intDamage);
	virtual std::string getType();
	virtual void setType(std::string strType);
	virtual int getAccuracy();
	virtual void setAccuracy(int intAccuracy);
	virtual long getRange();
	virtual void setRange(long lngRange);
	virtual std::string getAmmoType();
	virtual void setAmmoType(std::string strAmmoType);
protected:

private:
	int m_intDamage;
	std::string m_strType;
	int m_intAccuracy;
	long m_lngRange;
	std::string m_strAmmoType;
};

#endif