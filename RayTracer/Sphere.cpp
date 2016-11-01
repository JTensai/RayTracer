#include "Sphere.h"
#include <iostream>



Sphere::Sphere(glm::vec3 center, float radius, Material* material)
{
	this->center = center;
	this->radius = radius;
	this->mat = material;
}

std::string Sphere::getType() { 
	return "Sphere"; 
}

Sphere::~Sphere()
{
}
