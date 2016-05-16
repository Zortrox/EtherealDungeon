#include "Potion.h"
#include "Player.h"

Potion::Potion()
{

}
Potion::~Potion()
{

}
bool Potion::use(Creature &playerRef, std::string &strMessage)
{
	Player* tempPlayer = dynamic_cast<Player*>(&playerRef);
	if (tempPlayer->getHP() != tempPlayer->getMaxHP())
	{
		strMessage = "You used a potion to fully restore your health!";
		tempPlayer->setHP(tempPlayer->getMaxHP());
		return true;
	}
	else
	{
		strMessage = "Your health is already full";
		return false;
	}
}

Potion* Potion::clone()
{
	return new Potion(*this);
}

//XML Stuff
void Potion::dumpObject()
{
	std::cout << "Potion:" << std::endl;
	dumpObjectData();
}
void Potion::dumpObjectData()
{
	Consumable::dumpObjectData();
}
void Potion::writeFragment(std::ostream & output)
{
	output << "	<Potion>" << std::endl;
	writeDataAsFragment(output);
	output << "	</Potion>" << std::endl;
}
void Potion::writeDataAsFragment(std::ostream & output)
{
	Consumable::writeDataAsFragment(output);
}
void Potion::setElementData(std::string sElementName, std::string sValue)
{
	Consumable::setElementData(sElementName, sValue);
}