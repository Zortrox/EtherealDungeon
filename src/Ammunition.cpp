#include "Ammunition.h"
#include "Player.h"

Ammunition::Ammunition()
{

}
Ammunition::~Ammunition()
{

}
void Ammunition::memberName()
{

}

Ammunition* Ammunition::clone()
{
	return new Ammunition(*this);
}
bool Ammunition::equip(Creature &playerRef)
{
	Player* tempPlayer = dynamic_cast<Player*>(&playerRef);

	if (tempPlayer != NULL)
	{

	}

	return false;
}

//XML Stuff
void Ammunition::dumpObject()
{
	std::cout << "Ammunition:" << std::endl;
	dumpObjectData();
}
void Ammunition::dumpObjectData()
{
	Item::dumpObjectData();

	std::cout << "	- DamageBonus = " << getDamageBonus() << std::endl;
	std::cout << "	- Type = " << getType() << std::endl;
}
void Ammunition::writeFragment(std::ostream & output)
{
	output << "	<Ammunition>" << std::endl;
	writeDataAsFragment(output);
	output << "	</Ammunition>" << std::endl;
}
void Ammunition::writeDataAsFragment(std::ostream & output)
{
	Item::writeDataAsFragment(output);

	if (getDamageBonus() > -1) output << "		<damagebonus>" << getDamageBonus() << "</damagebonus>" << std::endl;
	if (getType() != "") output << "		<type>" << getType() << "</type>" << std::endl;
}
void Ammunition::setElementData(std::string sElementName, std::string sValue)
{
	Item::setElementData(sElementName, sValue);
	if (sElementName == "damagebonus")
	{
		setDamageBonus(atoi(sValue.c_str()));
	}
	else if (sElementName == "type")
	{
		setType(sValue);
	}
}

//getters & setters
void Ammunition::setDamageBonus(int intDamageBonus)
{
	m_intDamageBonus = intDamageBonus;
}
int Ammunition::getDamageBonus()
{
	return m_intDamageBonus;
}
void Ammunition::setType(std::string strType)
{
	m_strType = strType;
}
std::string Ammunition::getType()
{
	return m_strType;
}