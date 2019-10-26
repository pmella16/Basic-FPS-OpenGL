#ifndef PLAYGROUND_H
#define PLAYGROUND_H

// Include GLEW
#include <GL/glew.h>
// Include GLM
#include <glm/glm.hpp>

//some global variables for handling the vertex buffer
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
float curr_angle;
float r_axis_x=0;
float r_axis_y=0;
float r_axis_z=0;

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
