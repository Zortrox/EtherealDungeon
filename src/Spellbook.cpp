#include "Spellbook.h"
#include "Player.h"

Spellbook::Spellbook()
{

}
Spellbook::~Spellbook()
{

}
void Spellbook::use()
{

}

Spellbook* Spellbook::clone()
{
	return new Spellbook(*this);
}
bool Spellbook::equip(Creature &playerRef)
{
	Player* tempPlayer = dynamic_cast<Player*>(&playerRef);

	if (tempPlayer != NULL)
	{

	}

	return false;
}

//XML Stuff
void Spellbook::dumpObject()
{
	std::cout << "Spellbook:" << std::endl;
	dumpObjectData();
}
void Spellbook::dumpObjectData()
{
	Weapon::dumpObjectData();
}
void Spellbook::writeFragment(std::ostream & output)
{
	output << "	<Spellbook>" << std::endl;
	writeDataAsFragment(output);
	output << "	</Spellbook>" << std::endl;
}
void Spellbook::writeDataAsFragment(std::ostream & output)
{
	Weapon::writeDataAsFragment(output);
}
void Spellbook::setElementData(std::string sElementName, std::string sValue)
{
	Weapon::setElementData(sElementName, sValue);
}