#include "Item.h"

using namespace std;

Item::Item()
{

}
Item::~Item()
{

}
std::string Item::getDescription()
{
	return "";
}

Item* Item::clone()
{
	return new Item(*this);
}

bool Item::use(Creature &playerRef, string &strMessage)
{
	strMessage = "You cannot use this item";
	return false;
}
bool Item::equip(Creature &playerRef, string &strMessage)
{
	strMessage = "You cannot equip this item";
	return false;
}

//XML Stuff
void Item::dumpObject()
{
	std::cout << "Item:" << std::endl;
	dumpObjectData();
}
void Item::dumpObjectData()
{
	Entity::dumpObjectData();

	std::cout << "	- Weight = " << getWeight() << std::endl;
	std::cout << "	- Value = " << getValue() << std::endl;
	std::cout << "	- Rarity = " << getRarity() << std::endl;
	std::cout << "	- Enchantment = " << getEnchantment() << std::endl;
	std::cout << "	- Quantity = " << getQuantity() << std::endl;
}
void Item::writeFragment(std::ostream & output)
{
	output << "	<Item>" << std::endl;
	writeDataAsFragment(output);
	output << "	</Item>" << std::endl;
}
void Item::writeDataAsFragment(std::ostream & output)
{
	Entity::writeDataAsFragment(output);

	if (getWeight() > -1) output << "		<weight>" << getWeight() << "</weight>" << std::endl;
	if (getValue() > -1) output << "		<value>" << getValue() << "</value>" << std::endl;
	if (getRarity() > -1) output << "		<rarity>" << getRarity() << "</rarity>" << std::endl;
	if (getEnchantment() > -1) output << "		<enchantment>" << getEnchantment() << "</enchantment>" << std::endl;
	if (getQuantity() > -1) output << "		<quantity>" << getQuantity() << "</quantity>" << std::endl;
}
void Item::setElementData(std::string sElementName, std::string sValue)
{
	Entity::setElementData(sElementName, sValue);
	if (sElementName == "weight")
	{
		setWeight(atoi(sValue.c_str()));
	}
	else if (sElementName == "value")
	{
		setValue(atoi(sValue.c_str()));
	}
	else if (sElementName == "rarity")
	{
		setRarity(atoi(sValue.c_str()));
	}
	else if (sElementName == "enchantment")
	{
		setEnchantment(atoi(sValue.c_str()));
	}
	else if (sElementName == "quantity")
	{
		setQuantity(atoi(sValue.c_str()));
	}
}

//getters & setters
int Item::getWeight()
{
	return m_intWeight;
}
int Item::getValue()
{
	return m_intValue;
}
int Item::getRarity()
{
	return m_intRarity;
}
int Item::getEnchantment()
{
	return m_intEnchantment;
}
int Item::getQuantity()
{
	return m_intQuantity;
}
void Item::setWeight(int intWeight)
{
	m_intWeight = intWeight;
}
void Item::setValue(int intValue)
{
	m_intValue = intValue;
}
void Item::setRarity(int intRarity)
{
	m_intRarity = intRarity;
}
void Item::setEnchantment(int intEnchantment)
{
	m_intEnchantment = intEnchantment;
}
void Item::setQuantity(int intQuantity)
{
	m_intQuantity = intQuantity;
}