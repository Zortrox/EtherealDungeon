#include <iostream>
#include <string>
#include <fstream>

#include "parser.h"
#include "XMLSerializable.h"
#include "Entity.h"
#include "Ammunition.h"
#include "Armor.h"
#include "Consumable.h"
#include "Creature.h"
#include "Food.h"
#include "Gold.h"
#include "Item.h"
#include "Potion.h"
#include "Scroll.h"
#include "Spellbook.h"
#include "Wand.h"
#include "Weapon.h"

using namespace std;

bool parseElement(istream& input, string sHierarchy, vector<XMLSerializable*>& vObjects, bool& bNewObjects, int& iPos)
{	
	char c;
	string sElementName;

	do
	{
		c = input.get();

		if( c != '>' )
		{
			sElementName.push_back(c);
		}
	}
	while( c != '>' );

	string sContent;
	if (sHierarchy == "XML.World")
	{
		bNewObjects = true;
	}

	while( true )
	{
		c = input.get();

		if( c == '<' )
		{

			if( input.peek() == '/' )
			{
				input.get();
				string sEndTag;

				do
				{
					c = input.get();
					if( c != '>' )
						sEndTag.push_back(c);

				} while( c != '>' );

				if( sEndTag != sElementName )
				{
					cout << "Tag name mismatch" << endl;
					return false;
				}

				if (sHierarchy.find("XML.World.Entity") != -1)
				{
					if (bNewObjects)
					{
						Entity* objEntity = new Entity;
						vObjects.push_back(objEntity);
						iPos = vObjects.size() - 1;
						bNewObjects = false;
					}
					dynamic_cast<Entity*>(vObjects[iPos])->setElementData(sElementName, sContent);
				}
				else if (sHierarchy.find("XML.World.Item") != -1)
				{
					if (bNewObjects)
					{
						Item* objItem = new Item;
						vObjects.push_back(objItem);
						iPos = vObjects.size() - 1;
						bNewObjects = false;
					}
					dynamic_cast<Item*>(vObjects[iPos])->setElementData(sElementName, sContent);
				}
				else if (sHierarchy.find("XML.World.Creature") != -1)
				{
					if (bNewObjects)
					{
						Creature* objCreature = new Creature;
						vObjects.push_back(objCreature);
						iPos = vObjects.size() - 1;
						bNewObjects = false;
					}
					dynamic_cast<Creature*>(vObjects[iPos])->setElementData(sElementName, sContent);
				}
				else if (sHierarchy.find("XML.World.Weapon") != -1)
				{
					if (bNewObjects)
					{
						Weapon* objWeapon = new Weapon;
						vObjects.push_back(objWeapon);
						iPos = vObjects.size() - 1;
						bNewObjects = false;
					}
					dynamic_cast<Weapon*>(vObjects[iPos])->setElementData(sElementName, sContent);
				}
				else if (sHierarchy.find("XML.World.Gold") != -1)
				{
					if (bNewObjects)
					{
						Gold* objGold = new Gold;
						vObjects.push_back(objGold);
						iPos = vObjects.size() - 1;
						bNewObjects = false;
					}
					dynamic_cast<Gold*>(vObjects[iPos])->setElementData(sElementName, sContent);
				}
				else if (sHierarchy.find("XML.World.Consumable") != -1)
				{
					if (bNewObjects)
					{
						Consumable* objConsumable = new Consumable;
						vObjects.push_back(objConsumable);
						iPos = vObjects.size() - 1;
						bNewObjects = false;
					}
					dynamic_cast<Consumable*>(vObjects[iPos])->setElementData(sElementName, sContent);
				}
				else if (sHierarchy.find("XML.World.Armor") != -1)
				{
					if (bNewObjects)
					{
						Armor* objArmor = new Armor;
						vObjects.push_back(objArmor);
						iPos = vObjects.size() - 1;
						bNewObjects = false;
					}
					dynamic_cast<Armor*>(vObjects[iPos])->setElementData(sElementName, sContent);
				}
				else if (sHierarchy.find("XML.World.Ammunition") != -1)
				{
					if (bNewObjects)
					{
						Ammunition* objAmmunition = new Ammunition;
						vObjects.push_back(objAmmunition);
						iPos = vObjects.size() - 1;
						bNewObjects = false;
					}
					dynamic_cast<Ammunition*>(vObjects[iPos])->setElementData(sElementName, sContent);
				}
				else if (sHierarchy.find("XML.World.Wand") != -1)
				{
					if (bNewObjects)
					{
						Wand* objWand = new Wand;
						vObjects.push_back(objWand);
						iPos = vObjects.size() - 1;
						bNewObjects = false;
					}
					dynamic_cast<Wand*>(vObjects[iPos])->setElementData(sElementName, sContent);
				}
				else if (sHierarchy.find("XML.World.Spellbook") != -1)
				{
					if (bNewObjects)
					{
						Spellbook* objSpellbook = new Spellbook;
						vObjects.push_back(objSpellbook);
						iPos = vObjects.size() - 1;
						bNewObjects = false;
					}
					dynamic_cast<Spellbook*>(vObjects[iPos])->setElementData(sElementName, sContent);
				}
				else if (sHierarchy.find("XML.World.Scroll") != -1)
				{
					if (bNewObjects)
					{
						Scroll* objScroll = new Scroll;
						vObjects.push_back(objScroll);
						iPos = vObjects.size() - 1;
						bNewObjects = false;
					}
					dynamic_cast<Scroll*>(vObjects[iPos])->setElementData(sElementName, sContent);
				}
				else if (sHierarchy.find("XML.World.Potion") != -1)
				{
					if (bNewObjects)
					{
						Potion* objPotion = new Potion;
						vObjects.push_back(objPotion);
						iPos = vObjects.size() - 1;
						bNewObjects = false;
					}
					dynamic_cast<Potion*>(vObjects[iPos])->setElementData(sElementName, sContent);
				}
				else if (sHierarchy.find("XML.World.Food") != -1)
				{
					if (bNewObjects)
					{
						Food* objFood = new Food;
						vObjects.push_back(objFood);
						iPos = vObjects.size() - 1;
						bNewObjects = false;
					}
					dynamic_cast<Food*>(vObjects[iPos])->setElementData(sElementName, sContent);
				}

				return true;
			}
			else
			{
				if( !parseElement(input, sHierarchy + "." + sElementName, vObjects, bNewObjects, iPos) )
				{
					return false;
				}

			}
		}
		else
		{
			if( c != '\n' )
				sContent.push_back(c);
		}

	}

	return true;
}

void outputXML(vector<XMLSerializable*> vObjects, ofstream& output)
{
	output << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << endl;
	output << "<World>" << endl;

	for (size_t i=0; i < vObjects.size(); i++)
	{
		vObjects[i]->writeFragment(output);
	}
	output << "</World>" << endl;
}

bool parseXML(istream & input, vector<XMLSerializable*>& vObjects)
{
	char c;

	do c = input.get();
	while( c != '<' );

	if( input.get() != '?' )
	{
		cout << "Invalid XML header" << endl;
		return false;
	}

	do c = input.get();
	while( c != '?' );

	if( input.get() != '>' )
	{
		cout << "Invalid XML header" << endl;
		return false;
	}

	do c = input.get();
	while( c != '<' );

	int iPos = 0;
	bool tmpFalse = false;
	return parseElement(input, "XML", vObjects, tmpFalse, iPos);
}


