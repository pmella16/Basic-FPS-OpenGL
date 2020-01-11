#include "map.h"

#include "common/objloader.hpp"
#include "common/texture.hpp"

/*
 * Constructor of map
 */
void Map::init(std::string path, std::string texture) {
	if (!loadOBJ(path.c_str(), vertices, uv_vertices, normals_vertices)) throw "Error importing OBJ file";

	textureID = loadBMP_custom(texture.c_str());

	if (textureID < 0) throw "Error importing texture.bmp";
}

/*
 * Function getCoords() gets all of the coordinates for the map
 */
std::vector<GLfloat> Map::getCoords() {
	std::vector<GLfloat> result;
	for (unsigned int i = 0; i < vertices.size(); i++) {
		//Push vertex i
		result.push_back(vertices.at(i).x);
		result.push_back(vertices.at(i).y);
		result.push_back(vertices.at(i).z);
		//Push uv vertex i
		result.push_back(uv_vertices.at(i).x);
		result.push_back(uv_vertices.at(i).y);
		//Push normal vertex i
		result.push_back(normals_vertices.at(i).x);
		result.push_back(normals_vertices.at(i).y);
		result.push_back(normals_vertices.at(i).z);
	}

	return result;
}

/*
 * Get the texture id obtained at construction
 */
GLuint Map::getTextureID() {
	return textureID;
}

GLuint Map::getCoordsVecSize() {
	return vertices.size() + uv_vertices.size() + normals_vertices.size();
}
