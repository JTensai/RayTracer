#include "Triangle.h"



Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, Material* material)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->mat = material;
}

std::string Triangle::getType(){ 
	return "Triangle"; 
}

Triangle::~Triangle()
{
}
