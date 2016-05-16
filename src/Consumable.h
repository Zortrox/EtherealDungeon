#pragma once

#ifndef _Consumable_included_
#define _Consumable_included_

#include "Item.h"

class Consumable: public Item {
public:
	Consumable();
	virtual ~Consumable();
	virtual bool use(Creature &playerRef, std::string &strMessage);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual Consumable* clone();

	//getters & setters
	virtual void setHealth(int intHealth);
	virtual int getHealth();
	virtual void setNutrition(int intNutrition);
	virtual int getNutrition();
protected:

private:
	int m_intHealth;
	int m_intNutrition;
};

#endif