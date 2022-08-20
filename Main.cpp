#define GLFW_INCLUDE_NONE
#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<glm/glm/gtc/type_ptr.hpp>
#include"shaderClass.h"
#include"Rect2D.h"
#include<glm/glm/gtx/string_cast.hpp>
#include"GOLCell.h"

using namespace std;

const int width = 800;
const int height = 800;

//some boilerplate code for outputting OGL errors
void GLAPIENTRY MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}

std::array<std::array<GOLCell, height>, width> playfield;

int main() {

	

	

	glfwInit();
	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
	
	//create opengl window
	GLFWwindow* window = glfwCreateWindow(width, height, "Simulation", NULL, NULL);

	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL(glfwGetProcAddress);
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	//enabling debug output for OGL
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(MessageCallback, 0);
	
	//define two squares of different colors and positions
	Rect2D rect1 = Rect2D(glm::vec3(20.0f, 20.0f, 1.0f), glm::vec3(0.3f, 0.5f, 0.3f), glm::vec3(400.0f, 400.0f, 0.0f));
	Rect2D rect2 = Rect2D(glm::vec3(20.0f, 20.0f, 1.0f), glm::vec3(0.5f, 0.3f, 0.3f), glm::vec3(100.0f, 100.0f, 0.0f));

	//compile the shader program out of the default vertex and fragment shaders
	Shader shader = Shader("default1.vert", "default1.frag");
	
	// define +y as the 'up' direction
	glm::vec3 upDir = glm::vec3(0.0f, 1.0f, 0.0f);
	// define the camera position at z=-1
	glm::vec3 camPos = glm::vec3(0.0f, 0.0f, -1.0f);
	// we want to look in the direction of z = -5
	glm::vec3 lookTarget = glm::vec3(0.0f, 0.0f, -5.0f);
	glm::vec3 cameraDirection = glm::normalize(camPos - lookTarget);
	
	// define view (camera) matrix providing camera position, what direction to look in, and what way is up 
	glm::mat4 view = glm::lookAt(camPos, cameraDirection, upDir);

	//define orthogonal projection matrix
	glm::mat4 projection;
	projection = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, 0.1f, 10.0f);

	//NOTE: Each Rect2D object defines its own model matrix for positioning on the playfield.

	while (!glfwWindowShouldClose(window)) {
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		
		//tell ogl we're using the shader program defined above
		shader.use();
		//draw the two rectangles
		rect1.Draw(shader, view, projection);
		rect2.Draw(shader, view, projection);

		glUseProgram(0);
		// Swap the back buffer with the front buffer (make what we've drawn visible)
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}
	// Delete Window
	glfwDestroyWindow(window);
	//Terminate GLFW
	glfwTerminate();
	cin.get();
}