#include "Tile.h"

using namespace std;

Tile::Tile()
{
	walkable = false;
	visible = true;
	upstairs = false;
	downstairs = false;
	beenSeen = false;
	tileCreature = NULL;
}

Tile::~Tile()
{

}

void Tile::setWalkable(bool walk)
{
	walkable = walk;
}
bool Tile::getWalkable()
{
	return walkable;
}

void Tile::setVisible(bool vis)
{
	visible = vis;
}
bool Tile::getVisible()
{
	return visible;
}

void Tile::setUpstairs(bool up)
{
	upstairs = up;
}
bool Tile::getUpstairs()
{
	return upstairs;
}

void Tile::setDownstairs(bool down)
{
	downstairs = down;
}
bool Tile::getDownstairs()
{
	return downstairs;
}

void Tile::setSeen(bool seen)
{
	beenSeen = seen;
}
bool Tile::getSeen()
{
	return beenSeen;
}

vector<Item*> Tile::getTileItemsVector()
{
	return vec_TileItems;
}
void Tile::setTileItemsVector(std::vector<Item*> iVec)
{
	vec_TileItems = iVec;
}
Creature* Tile::getTileCreature()
{
	return tileCreature;
}
void Tile::setTileCreature(Creature* creature)
{
	tileCreature = creature;
}