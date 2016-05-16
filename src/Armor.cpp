#include "Armor.h"
#include "Player.h"

Armor::Armor()
{

}
Armor::~Armor()
{

}

Armor* Armor::clone()
{
	return new Armor(*this);
}
bool Armor::equip(Creature &playerRef)
{
	Player* tempPlayer = dynamic_cast<Player*>(&playerRef);

	if (tempPlayer != NULL)
	{
		//get player inventory and switch current armor slot with one in inventory
	}

	return false;
}

//XML Stuff
void Armor::dumpObject()
{
	std::cout << "Armor:" << std::endl;
	dumpObjectData();
}
void Armor::dumpObjectData()
{
	Item::dumpObjectData();

	std::cout << "	- Slot = " << getSlot() << std::endl;
	std::cout << "	- Type = " << getType() << std::endl;
	std::cout << "	- ArmorType = " << getArmorType() << std::endl;
}
void Armor::writeFragment(std::ostream & output)
{
	output << "	<Armor>" << std::endl;
	writeDataAsFragment(output);
	output << "	</Armor>" << std::endl;
}
void Armor::writeDataAsFragment(std::ostream & output)
{
	Item::writeDataAsFragment(output);

	if (getSlot() != "") output << "		<slot>" << getSlot() << "</slot>" << std::endl;
	if (getType() != "") output << "		<type>" << getType() << "</type>" << std::endl;
	if (getArmorType() > -1) output << "		<armortype>" << getArmorType() << "</armortype>" << std::endl;
}
void Armor::setElementData(std::string sElementName, std::string sValue)
{
	Item::setElementData(sElementName, sValue);
	if (sElementName == "slot")
	{
		setSlot(sValue);
	}
	else if (sElementName == "type")
	{
		setType(sValue);
	}
	else if (sElementName == "armortype")
	{
		setArmorType(atoi(sValue.c_str()));
	}
}

//getters & setters
std::string Armor::getSlot()
{
	return m_strSlot;
}
void Armor::setSlot(std::string strSlot)
{
	m_strSlot = strSlot;
}
std::string Armor::getType()
{
	return m_strType;
}
void Armor::setType(std::string strType)
{
	m_strType = strType;
}
int Armor::getArmorType()
{
	return m_intArmorType;
}
void Armor::setArmorType(int intArmorType)
{
	m_intArmorType = intArmorType;
}