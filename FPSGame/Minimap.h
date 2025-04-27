#ifndef MINIMAP_h
#define MINIMAP_h

#include "Map.h"
#include <GL/glew.h>
#include <glm/glm.hpp>


class Minimap {
private:
	glm::vec4 cplane_x1;
	glm::vec4 cplane_x2;
	glm::vec4 cplane_y1;
	glm::vec4 cplane_y2;

	std::vector<vec3> miniMapCoords;
	GLfloat x_pos = (GLfloat) 0.7;
	GLfloat y_pos = -0.7;
	GLfloat edgeSize = 0.2;
    glm::vec3 houseColor = glm::vec3(0.44f, 0.225f, 0.03f);
    glm::vec3 floorColor = glm::vec3(0.6f,  0.6f,   0.6f);


public:
	Minimap() {};
	Minimap(std::string path);
	std::vector<GLfloat> getMiniMapCoords();
};

#endif
