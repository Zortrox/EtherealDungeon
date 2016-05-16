#include "Entity.h"

Entity::Entity()
{

}
Entity::~Entity()
{

}
bool Entity::hasProperty(std::string strProp)
{
	return true;
}
std::string Entity::getDescription()
{
	return "";
}

//XML Stuff
void Entity::dumpObject()
{
	std::cout << "Entity:" << std::endl;
	dumpObjectData();
}
void Entity::dumpObjectData()
{
	XMLSerializable::dumpObjectData();

	std::cout << "	- Name = " << getName() << std::endl;
	std::cout << "	- DisplayChar = " << getDisplayChar() << std::endl;
	std::cout << "	- Properties:" << std::endl;
	for (size_t i=0; i < m_vecProperties.size(); i++)
	{
		std::cout << "		- Property = " << m_vecProperties[i] << std::endl;
	}
}
void Entity::writeFragment(std::ostream & output)
{
	output << "	<Entity>" << std::endl;
	writeDataAsFragment(output);
	output << "	</Entity>" << std::endl;
}
void Entity::writeDataAsFragment(std::ostream & output)
{
	XMLSerializable::writeDataAsFragment(output);

	if (getName() != "") output << "		<name>" << getName() << "</name>" << std::endl;
	if (getDisplayChar() != NULL) output << "		<displayChar>" << getDisplayChar() << "</displayChar>" << std::endl;
	output << "		<properties>" << std::endl;
	for (size_t i=0; i < m_vecProperties.size(); i++)
	{
		if (m_vecProperties[i] != "") output << "			<property>" << m_vecProperties[i] << "</property>" << std::endl;
	}
	output << "		</properties>" << std::endl;
}
void Entity::setElementData(std::string sElementName, std::string sValue)
{
	if (sElementName == "name")
	{
		setName(sValue);
	}
	else if (sElementName == "displayChar")
	{
		setDisplayChar((*sValue.c_str()));
	}
	else if (sElementName == "property")
	{
		m_vecProperties.push_back(sValue);
	}
}

Entity* Entity::clone()
{
	return new Entity(*this);
}

//getters & setters
std::string Entity::getName()
{
	return m_strName;
}
void Entity::setName(std::string strName)
{
	m_strName = strName;
}
char Entity::getDisplayChar()
{
	return m_cDisplayChar;
}
void Entity::setDisplayChar(char cDisplayChar)
{
	m_cDisplayChar = cDisplayChar;
}
int Entity::getXPos()
{
	return xPos;
}
void Entity::setXPos(int X)
{
	xPos = X;
}
int Entity::getYPos()
{
	return yPos;
}
void Entity::setYPos(int Y)
{
	yPos = Y;
}