#pragma once
#include "Material.h"
#include <sstream>
#include "StaticHelpers.h"

class Shape
{
public:
	Shape();
	static Shape* parseAndCreateShape(std::string line);
	virtual std::string getType() = 0;
	virtual ~Shape();

	Material* mat;
};

