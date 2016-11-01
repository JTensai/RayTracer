#pragma once
#include "Shape.h"

class Sphere :
	public Shape
{
public:
	Sphere(glm::vec3 center, float radius, Material* material);
	std::string getType();
	virtual ~Sphere();

	glm::vec3 center;
	float radius;
};

