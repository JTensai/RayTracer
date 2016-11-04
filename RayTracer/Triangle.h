#pragma once
#include "Shape.h"
class Triangle :
	public Shape
{
public:
	Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, Material* material);
	std::string getType();
	float getHitLocationOnRay(glm::vec3 ray, glm::vec3 start_pos);
	glm::vec3 getNormalAtPoint(glm::vec3 point);
	virtual ~Triangle();

	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;
	glm::vec3 normal;
};

