#pragma once
#include <glm\glm.hpp>
#include <sstream>
#include "StaticHelpers.h"

class Material
{
public:
	Material();
	Material(std::stringstream &line);

	virtual ~Material();

	glm::vec3 diffuse;
	glm::vec3 specular_highlight;
	float phong_constant;
};

