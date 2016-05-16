#pragma once

#ifndef _CreatureFactory_included_
#define _CreatureFactory_included_

#include "Creature.h"

#include "parser.h"
#include <vector>
#include <random>
#include <fstream>
#include <time.h>

class CreatureFactory
{
public:	
	CreatureFactory();
	virtual ~CreatureFactory();
	Creature * generateCreature(int iMaxLevel);

private:
	std::vector<Creature*> vec_Creatures;
	std::mt19937 mt;
};

#endif
