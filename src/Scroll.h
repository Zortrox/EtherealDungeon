#pragma once

#ifndef _Scroll_included_
#define _Scroll_included_

#include "Consumable.h"

class Scroll: public Consumable {
public:
	Scroll();
	virtual ~Scroll();
	virtual bool use(Creature &playerRef, std::string &strMessage);
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual Scroll* clone();

	//getters & setters

protected:

private:

};

#endif