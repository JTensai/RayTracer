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

float Sphere::getHitLocationOnRay(glm::vec3 ray, glm::vec3 start_pos) {


	// http://www.ccs.neu.edu/home/fell/CSU540/programs/RayTracingFormulas.htm

	// check if we hit the sphere at all

	float dx = ray.x;
	float dy = ray.y;
	float dz = ray.z;
	
	float a = (dx * dx) + (dy * dy) + (dz * dz);
	float b = 2 * (dx*(start_pos.x - center.x) + dy*(start_pos.y - center.y) + dz*(start_pos.z - center.z));
	float c =
		start_pos.x * start_pos.x
		+ start_pos.y * start_pos.y
		+ start_pos.z * start_pos.z
		+ center.x * center.x
		+ center.y * center.y
		+ center.z * center.z
		- 2 * (start_pos.x * center.x)
		- 2 * (start_pos.y * center.y)
		- 2 * (start_pos.z * center.z)
		- radius * radius;


	float discriminant = (b * b) - (4 * a * c);

	if (discriminant < 0) {
		// no intersection
	}
	else {
		// ray intersects the sphere in 2 points AKA goes through it, need to find the two points
		float t1 = 0, t2 = 0;

		if (discriminant == 0) {
			// ray is tangent to sphere
			// pixel_color = scaleToInts(s->mat->diffuse, 255);
			t1 = t2 = -b / 2;
		}
		else {
			float square_root = sqrt(discriminant);
			t1 = (-b - square_root) / 2;
			t2 = (-b + square_root) / 2;
		}

		// sphere is in front of us
		if (t1 > 0) {
			return t1;
		}
		// we are inside the sphere
		else if (t2 > 0) {
			return t2;
		}
		// shere is behind us
		else {
			return 0;
			//intersection_point = glm::vec3();
			// no intersection
		}
	}
}

glm::vec3 Sphere::getNormalAtPoint(glm::vec3 point) {
	return glm::normalize(glm::vec3(
		(point.x - center.x) / radius,
		(point.y - center.y) / radius,
		(point.z - center.z) / radius
	));
}

Sphere::~Sphere()
{
}
