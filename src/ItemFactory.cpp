#include "ItemFactory.h"

using namespace std;

//TODO: Create item chance to drop instead of pure random

ItemFactory::ItemFactory()
{
	mt.seed( (long)time(NULL) );

	ifstream input;
	input.open("Items.xml");

	vector<XMLSerializable*> vWorld;
	parseXML(input, vWorld);

	input.close();

	for (size_t i = 0; i < vWorld.size(); i++)
	{
		XMLSerializable* pObject = vWorld.at(i);
		Item * pItem = dynamic_cast<Item*>(pObject);
		vec_Items.push_back(pItem);
	}

}

ItemFactory::~ItemFactory()
{
	for (size_t i = 0; i < vec_Items.size(); i++)
	{
		delete vec_Items.at(i);
	}
}

Item * ItemFactory::generateItem(int iMaxLevel)
{
	vector<Item*> tempItems;
	int rand;

	for (size_t i = 0; i < vec_Items.size(); i++)
	{
		tempItems.push_back(vec_Items.at(i));
	}

	rand = mt()%tempItems.size();

	Item * pReturnValue = tempItems.at(rand)->clone();

	//randomize gold value on creation
	if (pReturnValue->getName() == "gold"){pReturnValue->setValue((mt()%100)+1);}

	return pReturnValue;
}