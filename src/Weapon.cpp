#include "Weapon.h"
#include "Player.h"

Weapon::Weapon()
{

}
Weapon::~Weapon()
{

}

Weapon* Weapon::clone()
{
	return new Weapon(*this);
}
bool Weapon::equip(Creature &playerRef)
{
	Player* tempPlayer = dynamic_cast<Player*>(&playerRef);

	if (tempPlayer != NULL)
	{
		
	}

	return false;
}

//XML Stuff
void Weapon::dumpObject()
{
	std::cout << "Weapon:" << std::endl;
	dumpObjectData();
}
void Weapon::dumpObjectData()
{
	Item::dumpObjectData();

	std::cout << "	- Damage = " << getDamage() << std::endl;
	std::cout << "	- Type = " << getType() << std::endl;
	std::cout << "	- Accuracy = " << getAccuracy() << std::endl;
	std::cout << "	- Range = " << getRange() << std::endl;
	std::cout << "	- AmmoType = " << getAmmoType() << std::endl;
}
void Weapon::writeFragment(std::ostream & output)
{
	output << "	<Weapon>" << std::endl;
	writeDataAsFragment(output);
	output << "	</Weapon>" << std::endl;
}
void Weapon::writeDataAsFragment(std::ostream & output)
{
	Item::writeDataAsFragment(output);

	if (getDamage() > -1) output << "		<damage>" << getDamage() << "</damage>" << std::endl;
	if (getType() != "") output << "		<type>" << getType() << "</type>" << std::endl;
	if (getAccuracy() > -1) output << "		<accuracy>" << getAccuracy() << "</accuracy>" << std::endl;
	if (getRange() > -1) output << "		<range>" << getRange() << "</range>" << std::endl;
	if (getAmmoType() != "") output << "		<ammotype>" << getAmmoType() << "</ammotype>" << std::endl;
}
void Weapon::setElementData(std::string sElementName, std::string sValue)
{
	Item::setElementData(sElementName, sValue);
	if (sElementName == "damage")
	{
		setDamage(atoi(sValue.c_str()));
	}
	else if (sElementName == "type")
	{
		setType(sValue);
	}
	else if (sElementName == "accuracy")
	{
		setAccuracy(atoi(sValue.c_str()));
	}
	else if (sElementName == "range")
	{
		setRange(atoi(sValue.c_str()));
	}
	else if (sElementName == "ammotype")
	{
		setAmmoType(sValue);
	}
}

//getters & setters
int Weapon::getDamage()
{
	return m_intDamage;
}
void Weapon::setDamage(int intDamage)
{
	m_intDamage = intDamage;
}
std::string Weapon::getType()
{
	return m_strType;
}
void Weapon::setType(std::string strType)
{
	m_strType = strType;
}
int Weapon::getAccuracy()
{
	return m_intAccuracy;
}
void Weapon::setAccuracy(int intAccuracy)
{
	m_intAccuracy = intAccuracy;
}
long Weapon::getRange()
{
	return m_lngRange;
}
void Weapon::setRange(long lngRange)
{
	m_lngRange = lngRange;
}
std::string Weapon::getAmmoType()
{
	return m_strAmmoType;
}
void Weapon::setAmmoType(std::string strAmmoType)
{
	m_strAmmoType = strAmmoType;
}