#pragma once
#include <glm\glm.hpp>
#include <sstream>
#include <iostream>


static glm::vec3 parseVec3(std::stringstream &line) {
	std::string token;

	do {
		std::getline(line, token, ' ');
	} while (token == "");
	float x = stof(token);
	//std::cout << x << ", ";

	do {
		std::getline(line, token, ' ');
	} while (token == "");
	float y = stof(token);
	//std::cout << y << ", ";

	do {
		std::getline(line, token, ' ');
	} while (token == "");
	float z = stof(token);
	//std::cout << z << std::endl;

	return glm::vec3(x, y, z);
}

static glm::vec3 scaleToInts(glm::vec3 original, int scale_factor) {
	int r, g, b;
	r = (int)(original.x * scale_factor);
	g = (int)(original.y * scale_factor);
	b = (int)(original.z * scale_factor);
	return glm::vec3(r, g, b);
}