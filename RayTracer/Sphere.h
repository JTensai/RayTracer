#pragma once
#include "Shape.h"

class Sphere :
	public Shape
{
public:
	Sphere(glm::vec3 center, float radius, Material* material);
	virtual ~Sphere();

	glm::vec3 center;
	float radius;
};

