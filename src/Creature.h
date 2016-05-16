#pragma once

#ifndef _Creature_included_
#define _Creature_included_

#include "Entity.h"

class Item;
class Armor;
class Weapon;
class Scroll;
class Ammunition;

class Creature: public Entity {
public:
	Creature();
	virtual ~Creature();
	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(std::ostream & output);
	virtual void writeDataAsFragment(std::ostream & output);
	virtual void setElementData(std::string sElementName, std::string sValue);
	virtual bool attack(Creature* &monster, int dmg);

	//getters & setters
	virtual std::vector<Item*> getInventory();
	virtual void setInventory(std::vector<Item*> vecInv);
	virtual int getLevel();
	virtual void setLevel(int Level);
	virtual int getHP();
	virtual void setHP(int HP);
	virtual int getMaxHP();
	virtual void setMaxHP(int MaxHP);
	virtual bool getAction();
	virtual void setAction(bool action);

	Armor* getHelmet();
	void setHelmet(Armor* helmet);
	Armor* getChest();
	void setChest(Armor* chest);
	Armor* getGloves();
	void setGloves(Armor* gloves);
	Armor* getBoots();
	void setBoots(Armor* boots);
	Scroll* getMagic();
	void setMagic(Scroll* magic);
	Weapon* getWeapon();
	void setWeapon(Weapon* weapon);
	Ammunition* getAmmo();
	void setAmmo(Ammunition* ammo);

protected:
	int intLevel;
	int intHP;
	int intMaxHP;
	bool boolAction;
	std::vector<Item*> vec_Inventory;

	//Items
	//Add getters and setters
	Armor* equipped_Helmet;
	Armor* equipped_Chest;
	Armor* equipped_Gloves;
	Armor* equipped_Boots;
	Scroll* equipped_Magic;
	Weapon* equipped_Weapon;
	Ammunition* equipped_Ammo;
private:
	
};

#endif