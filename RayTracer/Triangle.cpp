#include "Triangle.h"
#include "glm\gtx\string_cast.hpp"


Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, Material* material)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->mat = material;
	normal = glm::cross(p3 - p1, p2 - p1);
	//normal = -normal;
	std::cout << glm::to_string(mat->diffuse) << std::endl;
}

std::string Triangle::getType(){ 
	return "Triangle"; 
}

float sign(glm::vec2 a, glm::vec2 b, glm::vec2 c) {
	return (a.x - c.x) * (b.y - c.y) - (b.x - c.x) * (a.y - c.y);
}

float Triangle::getHitLocationOnRay(glm::vec3 ray, glm::vec3 start_pos)
{
	float t = -glm::dot((start_pos - p1), normal) / glm::dot(ray, normal);

	if (t <= 0)
		return 0;

	glm::vec3 intersection = start_pos + t*ray;

	if (glm::dot(glm::cross(p2 - p1, intersection - p1), normal) < 0 &&
		glm::dot(glm::cross(p3 - p2, intersection - p2), normal) < 0 &&
		glm::dot(glm::cross(p1 - p3, intersection - p3), normal) < 0) 
	{
		return t;
	}

	return 0;





















	// All this garbage didn't work, see simple solution above


	float vd = glm::dot(normal, ray);
	if (vd == 0) {
		// ray is parallel to plane and does not intersect
		return 0;
	}
	//if (vd > 0) {
	//	// normal is pointing away from the ray and the plane is culled, unless it is a 2 sided triangle, but these are not
	//	return 0;
	//}

	float distance_from_origin_to_plane = -glm::dot(p1, normal);
	float vo = -(glm::dot(normal, start_pos) + distance_from_origin_to_plane);

	t = vo / vd;
	if (t < 0)
		return 0;

	glm::vec3 plane_intersect_point = start_pos + (ray * t);// (start_pos.x + ray.x * t, yo + ydt, zo + zdt)


	if (vd > 0)
		normal = -normal;



	float x_mag = abs(normal.x);
	float y_mag = abs(normal.y);
	float z_mag = abs(normal.z);

	glm::vec2 p1_uv, p2_uv, p3_uv, intersect_uv;

	if (x_mag > y_mag && x_mag > z_mag) {
		// x is greatest
		intersect_uv = glm::vec2(plane_intersect_point.y, plane_intersect_point.z);
		p1_uv = glm::vec2(p1.y, p1.z);
		p2_uv = glm::vec2(p2.y, p2.z);
		p3_uv = glm::vec2(p3.y, p3.z);
	}
	else if (y_mag > x_mag && y_mag > z_mag) {
		// y is greatest
		intersect_uv = glm::vec2(plane_intersect_point.x, plane_intersect_point.z);
		p1_uv = glm::vec2(p1.x, p1.z);
		p2_uv = glm::vec2(p2.x, p2.z);
		p3_uv = glm::vec2(p3.x, p3.z);
	}
	else {
		// z is greatest
		intersect_uv = glm::vec2(plane_intersect_point.x, plane_intersect_point.y);
		p1_uv = glm::vec2(p1.x, p1.y);
		p2_uv = glm::vec2(p2.x, p2.y);
		p3_uv = glm::vec2(p3.x, p3.y);
	}


	/*bool check1 = sign(intersect_uv, p1_uv, p2_uv);
	bool check2 = sign(intersect_uv, p2_uv, p3_uv);
	bool check3 = sign(intersect_uv, p3_uv, p1_uv);

	bool inside_triangle = ((check1 == check2) && (check2 == check3));

	if (inside_triangle)
		return t;
	else
		return 0;*/

	p1_uv = p1_uv - intersect_uv;
	p2_uv = p2_uv - intersect_uv;
	p3_uv = p3_uv - intersect_uv;
	intersect_uv = glm::vec2(0, 0);


	int num_crossings = 0;
	int next_sign_holder = 0;
	int sign_holder = p1_uv.y < 0 ? -1 : 1;

	// loop through each point
	for (int i = 0; i < 3; i++) {
		int next_i = i + 1 == 3 ? 0 : i + 1;
		glm::vec2 cur, next;
		switch (i) {
		case 0:
			cur = p1_uv;
			next = p2_uv;
			break;
		case 1:
			cur = p2_uv;
			next = p3_uv;
			break;
		case 2:
			cur = p3_uv;
			next = p1_uv;
			break;
		}


		next_sign_holder = next.y < 0 ? -1 : 1;

		if (sign_holder != next_sign_holder) {
			if (cur.x > 0 && next.x > 0)
				num_crossings++;
			else if (cur.x > 0 || next.x > 0) {

				float u_cross = (cur.x - cur.y) * (next.x - cur.x) / (next.y - cur.y);
				if (u_cross > 0)
					num_crossings++;
			}
		}
		sign_holder = next_sign_holder;
	}
	

	bool inside_triangle = num_crossings % 2 == 0 ? false : true;

	if (inside_triangle)
		return t;
	else
		return 0;
}

glm::vec3 Triangle::getNormalAtPoint(glm::vec3 point)
{
	/*glm::vec3 edge_1, edge_2;
	edge_1 = p1 - p2;
	edge_2 = p3 - p2;*/
	return normal;// +point;
}

Triangle::~Triangle()
{
}
