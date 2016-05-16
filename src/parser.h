#pragma once

#ifndef _parser_included_
#define _parser_included_

#include <fstream>
#include <vector>

#include "XMLSerializable.h"

bool parseXML(std::istream & istream, std::vector<XMLSerializable*>& vObjects);
void outputXML(std::vector<XMLSerializable*> vObjects, std::ofstream& output);

#endif