#include "Scroll.h"

Scroll::Scroll()
{

}
Scroll::~Scroll()
{

}
bool Scroll::use(Creature &playerRef, std::string &strMessage)
{
	strMessage = "Your scroll burns up in your hands";
	return true;
}

Scroll* Scroll::clone()
{
	return new Scroll(*this);
}

//XML Stuff
void Scroll::dumpObject()
{
	std::cout << "Scroll:" << std::endl;
	dumpObjectData();
}
void Scroll::dumpObjectData()
{
	Consumable::dumpObjectData();
}
void Scroll::writeFragment(std::ostream & output)
{
	output << "	<Scroll>" << std::endl;
	writeDataAsFragment(output);
	output << "	</Scroll>" << std::endl;
}
void Scroll::writeDataAsFragment(std::ostream & output)
{
	Consumable::writeDataAsFragment(output);
}
void Scroll::setElementData(std::string sElementName, std::string sValue)
{
	Consumable::setElementData(sElementName, sValue);
}