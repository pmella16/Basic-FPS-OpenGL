#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;

class Map {
private:
	
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uv_vertices;
	std::vector<glm::vec3> normals_vertices;
	GLuint textureID;

public: 
	Map() {};
	void init(std::string path, std::string texture);
	std::vector<GLfloat> getCoords();
	GLuint getTextureID();
	GLuint getCoordsVecSize();
};

#endif