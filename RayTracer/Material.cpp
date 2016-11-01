#include "Material.h"

Material::Material() {

}

Material::Material(std::stringstream &line)
{
	std::string token;
	std::getline(line, token, ' ');
	while (std::getline(line, token, ' ')) {
		if (token == "Diffuse") {
			diffuse = parseVec3(line);
		}
		else if (token == "SpecularHighlight") {
			specular_highlight = parseVec3(line);
		}
		else if (token == "PhongConstant") {
			phong_constant = stof(token);
		}
	}
}


Material::~Material()
{
}
