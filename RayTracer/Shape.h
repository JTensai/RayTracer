#pragma once
#include "Material.h"
#include <sstream>
#include "StaticHelpers.h"

class Shape
{
public:
	Shape();
	static Shape* parseAndCreateShape(std::stringstream &line);
	virtual ~Shape();

	Material* mat;
};

