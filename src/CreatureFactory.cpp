#include "CreatureFactory.h"

using namespace std;

//TODO: Create creature chance to spawn instead of pure random

CreatureFactory::CreatureFactory()
{
	mt.seed( (long)time(NULL) );

	ifstream input;
	input.open("Creatures.xml");

	vector<XMLSerializable*> vWorld;
	parseXML(input, vWorld);

	input.close();

	for (size_t i = 0; i < vWorld.size(); i++)
	{
		XMLSerializable* pObject = vWorld.at(i);
		Creature * pCreature = dynamic_cast<Creature*>(pObject);
		vec_Creatures.push_back(pCreature);
	}

}

CreatureFactory::~CreatureFactory()
{
	for (size_t i = 0; i < vec_Creatures.size(); i++)
	{
		delete vec_Creatures.at(i);
	}
}

Creature * CreatureFactory::generateCreature(int iMaxLevel)
{
	vector<Creature*> tempCreatures;
	int rand;

	for (size_t i = 0; i < vec_Creatures.size(); i++)
	{
		if (vec_Creatures.at(i)->getLevel() <= iMaxLevel)
		{
			tempCreatures.push_back(vec_Creatures.at(i));
		}
	}

	rand = mt()%tempCreatures.size();

	Creature * pReturnValue = new Creature(*tempCreatures.at(rand));

	return pReturnValue;
}