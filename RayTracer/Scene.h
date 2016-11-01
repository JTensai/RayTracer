#pragma once
#include <glm\glm.hpp>
#include <vector>
#include "Shape.h"

class Scene
{
public:
	Scene(std::string file_name);
	virtual ~Scene();

	glm::vec3 camera_look_at;
	glm::vec3 camera_look_from;
	glm::vec3 camera_look_up;
	float field_of_view;
	glm::vec3 direction_to_light;
	glm::vec3 light_color;
	glm::vec3 ambient_light;
	glm::vec3 background_color;
	std::vector<Shape*> shapes;
};

