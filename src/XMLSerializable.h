#pragma once

#ifndef _XMLSerializable_included_
#define _XMLSerializable_included_

#include <string>
#include <iostream>

class XMLSerializable{
public:
	XMLSerializable();
	virtual ~XMLSerializable();
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);

	virtual XMLSerializable* clone() = 0;
protected:

private:
	
};

#endif