#pragma once
#include <glm\glm.hpp>
#include <vector>

class Image
{
public:
	Image(int width, int height);
	virtual ~Image();

	glm::vec3 getPixel(int row, int column);
	void addNextPixel(glm::vec3 pixel);
	void setPixel(int row, int column, glm::vec3 pixel);
	bool save(std::string file_name);

	int width = 0;
	int height = 0;
	std::vector<glm::vec3> pixels;
};

