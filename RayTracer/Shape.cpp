#include "Shape.h"
#include "Sphere.h"
#include "Triangle.h"


Shape::Shape()
{
}

Shape* Shape::parseAndCreateShape(std::stringstream &line)
{
	std::string token;
	std::getline(line, token, ' ');
	Material* material;
	if (token == "Sphere") {
		glm::vec3 center;
		float radius = 0;
		while (std::getline(line, token, ' ')) {
			if (token == "Center") {
				glm::vec3 center = parseVec3(line);
			}
			else if (token == "Radius") {
				std::getline(line, token, ' ');
				float radius = stof(token);
			}
			else if (token == "Material") {
				material = new Material(line);
			}
		}

		return new Sphere(center, radius, material);
	}
	if (token == "Triangle") {
		return new Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	}
	return new Shape();
}

Shape::~Shape()
{
}
