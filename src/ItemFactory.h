#pragma once

#ifndef _ItemFactory_included_
#define _ItemFactory_included_

#include "Item.h"

#include <vector>
#include <random>
#include <fstream>
#include "parser.h"
#include <time.h>

class ItemFactory
{
public:	
	ItemFactory();
	virtual ~ItemFactory();
	Item * generateItem(int iMaxLevel);

private:
	std::vector<Item*> vec_Items;
	std::mt19937 mt;
};

#endif