#include "Triangle.h"
#include "glm\gtx\string_cast.hpp"


Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, Material* material)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->mat = material;
	normal = glm::normalize(glm::cross(p3 - p1, p2 - p1));
	std::cout << glm::to_string(mat->diffuse) << std::endl;
}

std::string Triangle::getType(){ 
	return "Triangle"; 
}

float sign(glm::vec2 a, glm::vec2 b, glm::vec2 c) {
	return (a.x - c.x) * (b.y - c.y) - (b.x - c.x) * (a.y - c.y);
}

float Triangle::getHitLocationOnRay(glm::vec3 ray, glm::vec3 start_pos)
{
	float t = -glm::dot((start_pos - p1), normal) / glm::dot(ray, normal);

	if (t <= 0)
		return 0;

	glm::vec3 intersection = start_pos + t*ray;

	if (glm::dot(glm::cross(p2 - p1, intersection - p1), normal) < 0 &&
		glm::dot(glm::cross(p3 - p2, intersection - p2), normal) < 0 &&
		glm::dot(glm::cross(p1 - p3, intersection - p3), normal) < 0) 
	{
		return t;
	}

	return 0;
}

glm::vec3 Triangle::getNormalAtPoint(glm::vec3 point)
{
	return normal;
}

Triangle::~Triangle()
{
}
