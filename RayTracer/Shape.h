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
	virtual float getHitLocationOnRay(glm::vec3 ray, glm::vec3 start_pos) = 0;
	virtual glm::vec3 getNormalAtPoint(glm::vec3 point) = 0;
	virtual ~Shape();

	Material* mat;
};

