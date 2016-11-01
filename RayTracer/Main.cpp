#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtx\string_cast.hpp>
#include "Scene.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Image.h"
//#include <math.h>

void print(std::string s) {
	std::cout << s << std::endl;
}

int main() {
	Scene scene("./res/diffuse.rayTracing");
	
	int num_cols = 500;
	int num_rows = 500;
	Image image(num_cols, num_rows);

	float x_fov = glm::radians(scene.field_of_view);
	float y_fov = glm::radians(scene.field_of_view);

	// start rays from the top left
	float left = -tan(x_fov);
	float top = tan(y_fov);

	float current_x = left, current_y = top;

	float horizontal_step = (-left * 2) / image.width;
	float vertical_step = (top * 2) / image.height;

	glm::vec3 cam = scene.camera_look_from;

	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {
			// for each pixel, calculate its color, and add it to the image
			glm::vec3 pixel_color = scaleToInts(scene.background_color, 255);
			
			// calculate the source ray
			glm::vec3 ray = glm::vec3(current_x, current_y, 0) - scene.camera_look_from;
			ray = glm::normalize(ray);

			float dx = ray.x;
			float dy = ray.y;
			float dz = ray.z;

			for (Shape* s : scene.shapes) {
				if (s != nullptr) {
					if (s->getType() == "Sphere") {

						// http://www.ccs.neu.edu/home/fell/CSU540/programs/RayTracingFormulas.htm


						Sphere* sphere = dynamic_cast<Sphere*>(s);

						float a = (dx * dx) + (dy * dy) + (dz * dz);
						float b = 2 * (dx*(cam.x - sphere->center.x) + dy*(cam.y - sphere->center.y) + dz*(cam.z - sphere->center.z));
						float c = 
							cam.x * cam.x
							+ cam.y * cam.y
							+ cam.z * cam.z
							+ sphere->center.x * sphere->center.x
							+ sphere->center.y * sphere->center.y
							+ sphere->center.z * sphere->center.z
							- 2 * (cam.x * sphere->center.x)
							- 2 * (cam.y * sphere->center.y)
							- 2 * (cam.z*sphere->center.z)
							- sphere->radius * sphere->radius;

						
						float discriminant = (b * b) - (4 * a * c);

						if (discriminant < 0) {
							// no intersection
							//pixel_color = scaleToInts(glm::vec3(0,1,0), 255);
							//continue;
						}
						else if (discriminant == 0) {
							//std::cout << "Discriminant: " << discriminant << std::endl;
							// ray is tangent to sphere
							pixel_color = scaleToInts(s->mat->diffuse, 255);
						}
						else {
							// ray intersects the sphere in 2 points AKA goes through it, need to find the two points
							float square_root = sqrt(discriminant);
							float t1 = -b - square_root;
							float t2 = -b + square_root;



							//if (t1 > 0) {
								// sphere is in front of us
								glm::vec3 first_intersect, second_intersect;
								if (t1 < t2) {
									first_intersect = cam + ray * t1;
									second_intersect = cam + ray * t2;
								}
								else {
									first_intersect = cam + ray * t2;
									second_intersect = cam + ray * t1;
								}

								glm::vec3 n(
									(first_intersect.x - sphere->center.x) / sphere->radius,
									(first_intersect.y - sphere->center.y) / sphere->radius,
									(first_intersect.z - sphere->center.z) / sphere->radius
								);

								float num = glm::dot(n, scene.direction_to_light);
								//std::cout << num << std::endl;

								float kd = 0.9f;
								float ka = 0.1f;

								glm::vec3 calculated_color((s->mat->diffuse * kd * num) + (s->mat->diffuse * ka));
								//glm::vec3 calculated_color((kd*num*color.x + ka*color.x, kd*num*color.y + ka*color.y, kd*num*color.z + ka*color.z));


								pixel_color = scaleToInts(s->mat->diffuse, 255);
							//}
							//else if (t2 > 0) {
							//	// we are inside the sphere
							//}
							//else {
							//	// sphere is behind the camera
							//}


							
						}
					}
					if (s->getType() == "Triangle") {
						//std::cout << glm::to_string(dynamic_cast<Triangle*>(s)->p1) << std::endl;
					}
				}
			}


			image.addNextPixel(pixel_color);
			current_x += horizontal_step;
		}
		current_x = left;
		current_y -= vertical_step;
	}



	image.save("./output/output_image.ppm");

	return 0;
}
