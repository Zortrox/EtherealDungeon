#include "Consumable.h"
#include "Player.h"

Consumable::Consumable()
{

}
Consumable::~Consumable()
{

}
bool Consumable::use(Creature &playerRef, std::string &strMessage)
{
	Player* tempPlayer = dynamic_cast<Player*>(&playerRef);
	if (getName() == "oil flask")
	{
		if (tempPlayer->getOil() < 160)
		{
			strMessage = "You filled your lantern up a little bit";
			tempPlayer->setOil(tempPlayer->getOil() + 20);
			return true;
		}
		else
		{
			strMessage = "Your lantern is full";
		}
	}
	return false;
}

Consumable* Consumable::clone()
{
	return new Consumable(*this);
}

//XML Stuff
void Consumable::dumpObject()
{
	std::cout << "Consumable:" << std::endl;
	dumpObjectData();
}
void Consumable::dumpObjectData()
{
	Item::dumpObjectData();

	std::cout << "	- Health = " << getHealth() << std::endl;
	std::cout << "	- Nutrition = " << getNutrition() << std::endl;
}
void Consumable::writeFragment(std::ostream & output)
{
	output << "	<Consumable>" << std::endl;
	writeDataAsFragment(output);
	output << "	</Consumable>" << std::endl;
}
void Consumable::writeDataAsFragment(std::ostream & output)
{
	Item::writeDataAsFragment(output);

	if (getHealth() > -1) output << "		<health>" << getHealth() << "</health>" << std::endl;
	if (getNutrition() > -1) output << "		<nutrition>" << getNutrition() << "</nutrition>" << std::endl;
}
void Consumable::setElementData(std::string sElementName, std::string sValue)
{
	Item::setElementData(sElementName, sValue);
	if (sElementName == "health")
	{
		setHealth(atoi(sValue.c_str()));
	}
	else if (sElementName == "armortype")
	{
		setNutrition(atoi(sValue.c_str()));
	}
}

//getters & setters
void Consumable::setHealth(int intHealth)
{
	m_intHealth = intHealth;
}
int Consumable::getHealth()
{
	return m_intHealth;
}
void Consumable::setNutrition(int intNutrition)
{
	m_intNutrition = intNutrition;
}
int Consumable::getNutrition()
{
	return m_intNutrition;
}