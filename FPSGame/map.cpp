#include "map.h"

#include "common/objloader.hpp"
#include "common/texture.hpp"

/*
 * Constructor of map
 */
void Map::init(std::string mappath, std::string texture, std::string sunpath) {
	//Load map obj
	if (!loadOBJ(mappath.c_str(), map_vertices, map_uv_vertices, map_normals_vertices)) throw "Error importing OBJ file for the map";

	textureID = loadBMP_custom(texture.c_str());

	//Load sun obj
	if (!loadOBJ(sunpath.c_str(), sun_vertices)) throw "Error importing OBJ file for the sun";

	//Traslate the sun to its initial position relative to the map
	for (unsigned int i = 0; i < sun_vertices.size(); i++) sun_vertices.at(i) += sun_position;

	if (textureID < 0) throw "Error importing texture.bmp";
}

/*
 * Function getCoords() gets all of the coordinates for the map
 */
std::vector<GLfloat> Map::getMapCoords() {
	std::vector<GLfloat> result;
	for (unsigned int i = 0; i < map_vertices.size(); i++) {
		//Push vertex i
		result.push_back(map_vertices.at(i).x);
		result.push_back(map_vertices.at(i).y);
		result.push_back(map_vertices.at(i).z);
		//Push uv vertex i
		result.push_back(map_uv_vertices.at(i).x);
		result.push_back(map_uv_vertices.at(i).y);
		//Push normal vertex i
		result.push_back(map_normals_vertices.at(i).x);
		result.push_back(map_normals_vertices.at(i).y);
		result.push_back(map_normals_vertices.at(i).z);
	}

	return result;
}

std::vector<GLfloat> Map::getSunCoords() {
	std::vector<GLfloat> result;
	for (unsigned int i = 0; i < sun_vertices.size(); i++) {
		result.push_back(sun_vertices.at(i).x);
		result.push_back(sun_vertices.at(i).y);
		result.push_back(sun_vertices.at(i).z);
	}
	return result;
}

/*
 * Get the texture id obtained at construction
 */
GLuint Map::getTextureID() {
	return textureID;
}

GLuint Map::getMapCoordsVecSize() {
	return map_vertices.size() + map_uv_vertices.size() + map_normals_vertices.size();
}

GLuint Map::getSunCoordsVecSize() {
	return sun_vertices.size();
}

GLfloat* Map::getSunPosition() {
	GLfloat result[] = { sun_position[0], sun_position[1], sun_position[2] };
	return result;
}
