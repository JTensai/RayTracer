#include "Sphere.h"



Sphere::Sphere(glm::vec3 center, float radius, Material* material)
{
	this->center = center;
	this->radius = radius;
	this->mat = material;
}


Sphere::~Sphere()
{
}
