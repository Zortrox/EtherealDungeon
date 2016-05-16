#pragma once

#ifndef _Item_included_
#define _Item_included_

#include "Entity.h"
#include "Creature.h"
#include <string>
#include <vector>

class Item: public Entity {
public:
	Item();
	virtual ~Item();
	virtual std::string getDescription();
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual Item* clone();
	virtual bool use(Creature &playerRef, std::string &strMessage);
	virtual bool equip(Creature &playerRef, std::string &strMessage);

	//getters & setters
	virtual int getWeight();
	virtual int getValue();
	virtual int getRarity();
	virtual int getEnchantment();
	virtual int getQuantity();
	virtual void setWeight(int intWeight);
	virtual void setValue(int intValue);
	virtual void setRarity(int intRarity);
	virtual void setEnchantment(int intEnchantment);
	virtual void setQuantity(int intQuantity);
protected:

private:
	int m_intWeight;
	int m_intValue;
	int m_intRarity;
	int m_intEnchantment;
	int m_intQuantity;
};

#endif