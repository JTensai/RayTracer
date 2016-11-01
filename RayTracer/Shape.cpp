#include "Shape.h"
#include "Sphere.h"
#include "Triangle.h"
#include <iostream>
#include <glm\gtx\string_cast.hpp>


Shape::Shape()
{
}

Shape* Shape::parseAndCreateShape(std::string given_line)
{
	std::stringstream line(given_line);
	std::string token;

	// catch leading spaces before shape names
	do {
		std::getline(line, token, ' ');
	} while (token == "");

	//std::getline(line, token, ' ');
	if (token == "Sphere") {
		glm::vec3 center;
		float radius = 0;
		Material* material;
		while (std::getline(line, token, ' ')) {
			// catch extra spaces between sphere details
			if (token == "")
				continue;

			if (token == "Center") {
				center = parseVec3(line);
			}
			else if (token == "Radius") {
				do {
					std::getline(line, token, ' ');
				} while (token == "");
				float radius = stof(token);
			}
			else if (token == "Material") {
				material = new Material(line.str());
			}
		}

		return new Sphere(center, radius, material);
	}
	if (token == "Triangle") {		
		return new Triangle(parseVec3(line), parseVec3(line), parseVec3(line), new Material(line.str()));
	}
	return nullptr;
}

Shape::~Shape()
{
}
