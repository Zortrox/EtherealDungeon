#include "Food.h"

Food::Food()
{

}
Food::~Food()
{

}
bool Food::use(Creature &playerRef, std::string &strMessage)
{
	strMessage = "You eat some food";
	return true;
}

Food* Food::clone()
{
	return new Food(*this);
}

//XML Stuff
void Food::dumpObject()
{
	std::cout << "Food:" << std::endl;
	dumpObjectData();
}
void Food::dumpObjectData()
{
	Consumable::dumpObjectData();
}
void Food::writeFragment(std::ostream & output)
{
	output << "	<Food>" << std::endl;
	writeDataAsFragment(output);
	output << "	</Food>" << std::endl;
}
void Food::writeDataAsFragment(std::ostream & output)
{
	Consumable::writeDataAsFragment(output);
}
void Food::setElementData(std::string sElementName, std::string sValue)
{
	Consumable::setElementData(sElementName, sValue);
}