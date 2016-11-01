#include "Scene.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glm\gtx\string_cast.hpp>
#include "StaticHelpers.h"


Scene::Scene(std::string file_name)
{
	std::ifstream scene_file(file_name);
	std::string line;
	if (scene_file.is_open()) {
		while (std::getline(scene_file, line)) {
			// for each line in the file
			std::stringstream iss(line);
			std::string token;
			do {
				std::getline(iss, token, ' ');
			} while (token == "");

			if (token == "CameraLookAt") {
				camera_look_at = parseVec3(iss);
			}
			else if (token == "CameraLookFrom") {
				camera_look_from = parseVec3(iss);
			}
			else if (token == "CameraLookUp") {
				camera_look_up = parseVec3(iss);
			}
			else if (token == "FieldOfView") {
				do {
					std::getline(iss, token, ' ');
				} while (token == "");
				field_of_view = stof(token);
			}
			else if (token == "DirectionToLight") {
				direction_to_light = parseVec3(iss);

				do {
					std::getline(iss, token, ' ');
				} while (token == "");
				if (token == "LightColor") {
					light_color = parseVec3(iss);
				}
			}
			else if (token == "AmbientLight") {
				ambient_light = parseVec3(iss);
			}
			else if (token == "BackgroundColor") {
				background_color = parseVec3(iss);
			}
			// anything else should be a shape
			else  {
				shapes.push_back(Shape::parseAndCreateShape(iss.str()));			
			}
		}
	}
	else {
		std::cout << "Unable to open file: " << file_name << std::endl;
	}

}

Scene::~Scene()
{
	for (Shape* s : shapes) {
		delete s;
	}
}
