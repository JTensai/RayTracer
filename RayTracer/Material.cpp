#include "Material.h"

Material::Material() {

}

Material::Material(std::string given_line)
{
	std::stringstream line(given_line);
	std::string token;
	std::getline(line, token, ' ');
	while (std::getline(line, token, ' ')) {
		if (token == "")
			continue; 

		if (token == "Diffuse") {
			diffuse = parseVec3(line);
		}
		else if (token == "SpecularHighlight") {
			specular_highlight = parseVec3(line);
		}
		else if (token == "PhongConstant") {
			do {
				std::getline(line, token, ' ');
			} while (token == "");
			phong_constant = stof(token);
		}
	}
}


Material::~Material()
{
}
