#include "playground.h"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

//
#include <SOIL.h>

// Include GLM
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>


int main( void )
{
	  //Initialize window
	 bool windowInitialized = initializeWindow();
	 if (!windowInitialized) return -1;

	 //Initialize map
	 map.init();

	 //Initialize vertex buffer
	 bool vertexbufferInitialized = initializeVertexbuffer();
	 if (!vertexbufferInitialized) return -1;

	  // Create and compile our GLSL program from the shaders
	  programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

<<<<<<< Updated upstream
  //Initialize MVP matrix
  initializeMVPTransformation();

  curr_x = 0;
  curr_y = 0;
  curr_z = 0;
  curr_angle = 0;
=======
	//Initialize MVP matrix
	initializeMVPTransformation();

	curr_x = 0;
	 curr_y = 0;
	 curr_z = 0;

	 glEnable(GL_DEPTH_TEST);
>>>>>>> Stashed changes
	//start animation loop until escape key is pressed
	do{
		/*Update position of shapes by transformations or rotations depending on keys*/
		updatePositionLoop();
		/*DRAW THEM*/
		updateAnimationLoop();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	
	//Cleanup and close window
	cleanupVertexbuffer();
	glDeleteProgram(programID);
	closeWindow();
	return 0;
}

/*
	UPDATE ANIMATION LOOP
*/
void updateAnimationLoop()
{
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Use our shader
  glUseProgram(programID);

  //Initialize MVP matrix
  initializeMVPTransformation();
  //Apply transformations of updatePositionLoop
  MVP *= transformation;

  //Set the matrix as the uniform
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

  // 1rst attribute buffer : vertices
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
<<<<<<< Updated upstream
  glVertexAttribPointer(
	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,					// size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
  );
  
  //2nd attribute buffer: colors
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
=======
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *)0);
  
  //2nd attribute buffer: colors
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *)(3*sizeof(float)));
>>>>>>> Stashed changes
  
  // Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, vertexbuffer_size); // 3 indices starting at 0 -> 1 triangle

  //Disable vertexAttribArray
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);

  // Swap buffers
  glfwSwapBuffers(window);
  glfwPollEvents();
}

/*
	UPDATE POSITION OF ELEMENTS
*/
void updatePositionLoop() {

	//Generate transformation matrix
	if (glfwGetKey(window, GLFW_KEY_W)) curr_y += 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_S)) curr_y -= 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_A)) curr_x -= 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_D)) curr_x += 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_UP)) curr_z -= 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_DOWN)) curr_z += 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_R)) curr_angle += 0.01f;
	else if (glfwGetKey(window, GLFW_KEY_E)) curr_angle -= 0.01f;
	transformation[0][0] = 1.0; transformation[1][0] = 0.0; transformation[2][0] = 0.0; transformation[3][0] = curr_x;
	transformation[0][1] = 0.0; transformation[1][1] = 1.0; transformation[2][1] = 0.0; transformation[3][1] = curr_y;
	transformation[0][2] = 0.0; transformation[1][2] = 0.0; transformation[2][2] = 1.0; transformation[3][2] = curr_z;
	transformation[0][3] = 0.0; transformation[1][3] = 0.0; transformation[2][3] = 0.0; transformation[3][3] = 1.0;

}
/*
	INITIALIZE WINDOW
*/
bool initializeWindow()
{
  // Initialise GLFW
  if (!glfwInit())
  {
    fprintf(stderr, "Failed to initialize GLFW\n");
    getchar();
    return false;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  window = glfwCreateWindow(720, 480, "Testing graphics..", NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
    getchar();
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    return false;
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  return true;
}

/*
	INITIALIZE VERTEX BUFFER
*/
bool initializeVertexbuffer()
{
	//Generate vertices for triangles
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

<<<<<<< Updated upstream
  vertexbuffer_size = 9;
  static const GLfloat g_vertex_buffer_data[] = {
    -0.5f, -1.0f, 0.0f,	//Triangulo inf. izq
    -0.5f, 0.0f, 0.0f,
	0.5f, -1.0f, 0.0f,
	-0.5f, 0.0f, 0.0f, //Triangulo inf. der
	0.5f, 0.0f, 0.0f,
	0.5f, -1.0f, 0.0f,
	-0.5f, 0.0f, 0.0f, //Triangulo sup.
	0.5f, 0.0f, 0.0f,
	0.0f, 0.4f, 0.0f
  };

=======
  std::vector<float> vertex = map.getPosCoords();
  std::copy(vertex.begin(), vertex.end(), buffer);
  vertexbuffer_size = (sizeof(buffer)/sizeof(buffer[0]));
>>>>>>> Stashed changes
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);

  //Generate colors for vertices
  glGenVertexArrays(1, &ColorVAOid);
  glBindVertexArray(ColorVAOid);

  static const GLfloat g_color_buffer_data[] = {
	0.9f, 0.8f, 0.3f,	//Triangulo inf. izq
	0.9f, 0.8f, 0.3f,
	0.9f, 0.8f, 0.3f,
	0.9f, 0.8f, 0.3f, //Triangulo inf. der
	0.9f, 0.8f, 0.3f,
	0.9f, 0.8f, 0.3f,
	0.9f, 0.3f, 0.1f, //Triangulo sup.
	0.9f, 0.3f, 0.1f,
	0.9f, 0.3f, 0.1f,
  };

  glGenBuffers(1, &colorbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
  
  return true;
}

bool cleanupVertexbuffer()
{
  // Cleanup VBO
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteBuffers(1, &colorbuffer);
  glDeleteVertexArrays(1, &ColorVAOid);
  glDeleteVertexArrays(1, &VertexArrayID);
  return true;
}

bool initializeMVPTransformation()
{
	// Get a handle for our "MVP" uniform
	GLuint MatrixIDnew = glGetUniformLocation(programID, "MVP");
	MatrixID = MatrixIDnew;

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	//glm::mat4 Projection = glm::frustum(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
	// Camera matrix
	float distance = 8;
	glm::mat4 View = glm::lookAt(
<<<<<<< Updated upstream
		glm::vec3(0, distance/2, distance), // Camera is at (0,4,8), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
=======
		camera, // Camera is at (0,4,8), in World Space
		target, // and looks at the origin
>>>>>>> Stashed changes
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);

	Model = glm::rotate(Model, curr_angle, glm::vec3(0.0f, 1.0f, 0.0f));


	// Our ModelViewProjection : multiplication of our 3 matrices
	MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
	return true;

}

bool closeWindow()
{
  glfwTerminate();
  return true;
}

