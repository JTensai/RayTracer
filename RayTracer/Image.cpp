#include "Image.h"
#include <iostream>
#include <fstream>


Image::Image(int width, int height)
{
	this->width = width;
	this->height = height;
}


Image::~Image()
{
}

glm::vec3 Image::getPixel(int row, int column)
{
	unsigned int index = (this->width * row) + column;
	if (index > pixels.size() - 1)
		return glm::vec3();
	return pixels[index];
}

void Image::addNextPixel(glm::vec3 pixel)
{
	pixels.push_back(pixel);
}

void Image::setPixel(int row, int column, glm::vec3 pixel)
{
	unsigned int index = (this->width * row) + column;
	if (index > pixels.size() - 1)
		addNextPixel(pixel);
	else
		pixels[(this->width * row) + column] = pixel;
}

bool Image::save(std::string file_name)
{
	std::ofstream out(file_name);
	if (out.is_open()) {

		out << "P3\n" << width << " " << height << "\n1" << std::endl;
			//P3
			// Width Hieght
			// Max color value
			// # comments
			// topleft topmiddle topright
			// bottomleft bottommiddle bottomright

		for (int i = 0; i < this->height; i++) {
			for (int j = 0; j < this->width; j++) {
				out 
					<< getPixel(i, j).x << "\t" 
					<< getPixel(i, j).y << "\t" 
					<< getPixel(i, j).z << "\t";
			}
			out << "\n";
		}
		//out.close();
	}
	else {
		std::cout << "Failed to open output file :(" << std::endl;
	}


	return false;
}
