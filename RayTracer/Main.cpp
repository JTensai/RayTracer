#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtx\string_cast.hpp>
#include "Scene.h"

void print(std::string s) {
	std::cout << s << std::endl;
}

int main() {
	Scene scene("./res/diffuse.rayTracing");

	std::cout << scene.field_of_view << std::endl;

	return 0;
}
