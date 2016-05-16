#include "Gold.h"

Gold::Gold()
{

}
Gold::~Gold()
{

}
void Gold::pickUp()
{

}

Gold* Gold::clone()
{
	return new Gold(*this);
}

//XML Stuff
void Gold::dumpObject()
{
	std::cout << "Gold:" << std::endl;
	dumpObjectData();
}
void Gold::dumpObjectData()
{
	Item::dumpObjectData();
}
void Gold::writeFragment(std::ostream & output)
{
	output << "	<Gold>" << std::endl;
	writeDataAsFragment(output);
	output << "	</Gold>" << std::endl;
}
void Gold::writeDataAsFragment(std::ostream & output)
{
	Item::writeDataAsFragment(output);
}
void Gold::setElementData(std::string sElementName, std::string sValue)
{
	Item::setElementData(sElementName, sValue);
}