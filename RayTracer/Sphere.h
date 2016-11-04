#pragma once
#include "Shape.h"

class Sphere :
	public Shape
{
public:
	Sphere(glm::vec3 center, float radius, Material* material);
	std::string getType();
	float getHitLocationOnRay(glm::vec3 ray, glm::vec3 start_pos);
	glm::vec3 getNormalAtPoint(glm::vec3 point);
	virtual ~Sphere();

	glm::vec3 center;
	float radius;
};

