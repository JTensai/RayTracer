#pragma once
#include <glm\glm.hpp>
#include <sstream>


static glm::vec3 parseVec3(std::stringstream &line) {
	std::string token;
	std::getline(line, token, ' ');
	float x = stof(token);
	std::getline(line, token, ' ');
	float y = stof(token);
	std::getline(line, token, ' ');
	float z = stof(token);

	return glm::vec3(x, y, z);
}