#pragma once
#include "Shape.h"
class Triangle :
	public Shape
{
public:
	Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, Material* material);
	virtual ~Triangle();

	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;
};

