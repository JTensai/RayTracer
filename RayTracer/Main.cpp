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
	Scene scene("./res/SceneIII.rayTracing");
	
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

	glm::vec3 ray_origin = scene.camera_look_from;

	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {
			// for each pixel, calculate its color, and add it to the image
			glm::vec3 pixel_color = scaleToInts(scene.background_color, 255);
			
			// calculate the source ray
			glm::vec3 ray = glm::normalize(glm::vec3(current_x, current_y, 0) - scene.camera_look_from);

			float collision_t = 0;
			Shape* collision_shape = nullptr;


			// find the closest shape to the camera
			for (Shape* s : scene.shapes) {
				if (s != nullptr) {
					float hit_t = s->getHitLocationOnRay(ray, ray_origin);
					if (hit_t > 0 && (hit_t < collision_t || collision_t == 0)) {
						collision_t = hit_t;
						collision_shape = s;
					}
				}
			}


			// a collision occured on one of the shapes in front of the camera
			// collision_shape is the object closest to the camera that got hit
			if (collision_shape != nullptr) {
				glm::vec3 intersection_point = ray_origin + ray * collision_t;

				// Check if pixel is in shadow or not
				glm::vec3 shadow_ray = scene.direction_to_light;// - intersection_point;
				bool is_in_shadow = false;
				for (Shape* s : scene.shapes) {
					if (s != nullptr) {
						float hit_t = s->getHitLocationOnRay(shadow_ray, intersection_point + shadow_ray * 0.0001f);
						if (hit_t > 0) {
							is_in_shadow = true;
							break;
						}
					}
				}


				glm::vec3 phong = glm::vec3(0);
				float clamped_n_dot_l = 0;

				if (!is_in_shadow) {
					glm::vec3 normal = collision_shape->getNormalAtPoint(intersection_point);

					// angle between light and the normal
					float n_dot_l = glm::dot(normal, scene.direction_to_light);
					clamped_n_dot_l = glm::max(0.f, n_dot_l);
					
					// camera position
					glm::vec3 e = glm::normalize(scene.camera_look_from - intersection_point);
					// reflectance value
					glm::vec3 r = 2.f * normal * n_dot_l - scene.direction_to_light;
					float e_dot_r = glm::dot(e, r);
					float clamped_e_dot_r = glm::max(0.f, e_dot_r);
					
					phong = scene.light_color * collision_shape->mat->specular_highlight * pow(clamped_e_dot_r, collision_shape->mat->phong_constant);



					if (collision_shape->getType() == "Triangle") {
						//std::cout << glm::to_string(phong) << std::endl;
						if (glm::length(phong) > 0) {
							//phong = glm::vec3(1);
						}
					}
				}
				pixel_color = scaleToInts(collision_shape->mat->diffuse * (scene.ambient_light + (scene.light_color * clamped_n_dot_l)) + phong, 255);
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
