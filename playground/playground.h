#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "map.h"
// Include GLEW
#include <GL/glew.h>
// Include GLM
#include <glm/glm.hpp>

//Map variable;
Map map;

//some global variables for handling the vertex buffer

GLfloat buffer[n_vertexes];
GLuint vertexbuffer;
GLuint VertexArrayID;
GLuint vertexbuffer_size;
GLuint colorbuffer;
GLuint ColorVAOid;

//global variables to handle the MVP matrix
GLuint MatrixID;
glm::mat4 MVP;
glm::mat4 transformation;//additional transformation for the model

float curr_x;
float curr_y;
float curr_z;
float curr_angle = 0;
float c_x=0;
float c_y=(float)-0.4;
float c_z=0.5;
float t_x = 0;
float t_y = (float)-0.3;
float t_z = 0.0;
glm::vec3 camera = vec3(c_x, c_y, -c_z);
glm::vec3 target = vec3(t_x, t_y, -t_z);


//program ID of the shaders, required for handling the shaders with OpenGL
GLuint programID;

int main( void ); //<<< main function, called at startup
void updateAnimationLoop(); //<<< updates the animation loop
void updatePositionLoop(); //<<< Updates the position of the vertices depending on key presses
bool initializeMVPTransformation(); //<<< Generates the model-view-perspective matrix
bool initializeWindow(); //<<< initializes the window using GLFW and GLEW
bool initializeVertexbuffer(); //<<< initializes the vertex buffer array and binds it OpenGL
bool cleanupVertexbuffer(); //<<< frees all recources from the vertex buffer
bool closeWindow(); //<<< Closes the OpenGL window and terminates GLFW

#endif