#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtx\string_cast.hpp>
#include "Scene.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Image.h"

void print(std::string s) {
	std::cout << s << std::endl;
}

int main() {
	Scene scene("./res/diffuse.rayTracing");
	
	int num_cols = 100;
	int num_rows = 100;
	Image image(num_cols, num_rows);

	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {
			// for each pixel, calculate its color, and add it to the image
			glm::vec3 pixel_color = scaleToInts(scene.background_color, 255);




			for (Shape* s : scene.shapes) {
				if (s != nullptr) {
					if (s->getType() == "Sphere") {
						//std::cout << glm::to_string(dynamic_cast<Sphere*>(s)->center) << std::endl;
					}
					if (s->getType() == "Triangle") {
						//std::cout << glm::to_string(dynamic_cast<Triangle*>(s)->p1) << std::endl;
					}
				}
			}


			image.addNextPixel(pixel_color);
		}
	}



	image.save("./output/output_image.ppm");

	return 0;
}
