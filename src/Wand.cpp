#include "Wand.h"
#include "Player.h"

Wand::Wand()
{

}
Wand::~Wand()
{

}
void Wand::use()
{

}

Wand* Wand::clone()
{
	return new Wand(*this);
}
bool Wand::equip(Creature &playerRef)
{
	Player* tempPlayer = dynamic_cast<Player*>(&playerRef);

	if (tempPlayer != NULL)
	{

	}

	return false;
}

//XML Stuff
void Wand::dumpObject()
{
	std::cout << "Wand:" << std::endl;
	dumpObjectData();
}
void Wand::dumpObjectData()
{
	Weapon::dumpObjectData();
}
void Wand::writeFragment(std::ostream & output)
{
	output << "	<Wand>" << std::endl;
	writeDataAsFragment(output);
	output << "	</Wand>" << std::endl;
}
void Wand::writeDataAsFragment(std::ostream & output)
{
	Weapon::writeDataAsFragment(output);
}
void Wand::setElementData(std::string sElementName, std::string sValue)
{
	Weapon::setElementData(sElementName, sValue);
}