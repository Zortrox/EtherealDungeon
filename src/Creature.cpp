#include "Creature.h"
#include <cstdlib>

Creature::Creature()
{
	equipped_Helmet = NULL;
	equipped_Chest = NULL;
	equipped_Gloves = NULL;
	equipped_Boots = NULL;
	equipped_Magic = NULL;
	equipped_Weapon = NULL;
	equipped_Ammo = NULL;
}
Creature::~Creature()
{

}

//XML Stuff
void Creature::dumpObject()
{
	std::cout << "Entity:" << std::endl;
	dumpObjectData();
}
void Creature::dumpObjectData()
{
	Entity::dumpObjectData();

	std::cout << "	- Level = " << getLevel() << std::endl;
	std::cout << "	- HP = " << getHP() << std::endl;
	std::cout << "	- MaxHP = " << getMaxHP() << std::endl;
}
void Creature::writeFragment(std::ostream & output)
{
	output << "	<Creature>" << std::endl;
	writeDataAsFragment(output);
	output << "	</Creature>" << std::endl;
}
void Creature::writeDataAsFragment(std::ostream & output)
{
	Entity::writeDataAsFragment(output);

	if (getLevel() > -1) output << "		<level>" << getLevel() << "</level>" << std::endl;
	if (getHP() > -1) output << "		<HP>" << getHP() << "</HP>" << std::endl;
	if (getMaxHP() > -1) output << "		<maxHP>" << getMaxHP() << "</maxHP>" << std::endl;
}
void Creature::setElementData(std::string sElementName, std::string sValue)
{
	Entity::setElementData(sElementName, sValue);
	if (sElementName == "level")
	{
		setLevel(atoi(sValue.c_str()));
	}
	else if (sElementName == "HP")
	{
		setHP(atoi(sValue.c_str()));
	}
	else if (sElementName == "maxHP")
	{
		setMaxHP(atoi(sValue.c_str()));
	}
}

bool Creature::attack(Creature* &monster, int dmg)
{
	monster->setHP(monster->getHP() - dmg);

	if (monster->getHP() <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//getters & setters
std::vector<Item*> Creature::getInventory()
{
	return vec_Inventory;
}
void Creature::setInventory(std::vector<Item*> vecInv)
{
	vec_Inventory = vecInv;
}
int Creature::getLevel()
{
	return intLevel;
}
void Creature::setLevel(int Level)
{
	intLevel = Level;
}
int Creature::getHP()
{
	return intHP;
}
void Creature::setHP(int HP)
{
	intHP = HP;
}
int Creature::getMaxHP()
{
	return intMaxHP;
}
void Creature::setMaxHP(int MaxHP)
{
	intMaxHP = MaxHP;
}
bool Creature::getAction()
{
	return boolAction;
}
void Creature::setAction(bool action)
{
	boolAction = action;
}

//Equipped items
Armor* Creature::getHelmet()
{
	return equipped_Helmet;
}
void Creature::setHelmet(Armor* helmet)
{
	equipped_Helmet = helmet;
}
Armor* Creature::getChest()
{
	return equipped_Chest;
}
void Creature::setChest(Armor* chest)
{
	equipped_Chest = chest;
}
Armor* Creature::getGloves()
{
	return equipped_Gloves;
}
void Creature::setGloves(Armor* gloves)
{
	equipped_Gloves = gloves;
}
Armor* Creature::getBoots()
{
	return equipped_Boots;
}
void Creature::setBoots(Armor* boots)
{
	equipped_Boots = boots;
}
Scroll* Creature::getMagic()
{
	return equipped_Magic;
}
void Creature::setMagic(Scroll* magic)
{
	equipped_Magic = magic;
}
Weapon* Creature::getWeapon()
{
	return equipped_Weapon;
}
void Creature::setWeapon(Weapon* weapon)
{
	equipped_Weapon = weapon;
}
Ammunition* Creature::getAmmo()
{
	return equipped_Ammo;
}
void Creature::setAmmo(Ammunition* ammo)
{
	equipped_Ammo = ammo;
}