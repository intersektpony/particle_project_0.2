#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<glm/glm/gtc/type_ptr.hpp>
#include"shaderClass.h"
#include "Rect2D.h"

using namespace std;

int width = 800;
int height = 800;

//some boilerplate code for outputting OGL errors
void GLAPIENTRY MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}


int main() {
	glfwInit();
	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
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

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(MessageCallback, 0);
	
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	Rect2D rect = Rect2D(1, glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.3f, 0.3f, 0.3f));

	cout << rect.vertices[0] << endl;

	glBufferData(GL_ARRAY_BUFFER, sizeof(rect.vertices), rect.vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rect.indices), rect.indices, GL_STATIC_DRAW);


	Shader shader = Shader("default1.vert", "default1.frag");
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glm::vec3 position = glm::vec3(0.1f, 0.1f, 0.1f);
	glm::vec3 scale = glm::vec3(1000.0f, 1000.0f, 1000.0f);
	glm::mat4 rotation = glm::mat4(0.0f);
	glm::mat4 translation = glm::translate(glm::mat4(), position);
	glm::mat4 scaleMat = glm::scale(glm::mat4(), scale);
	glm::mat4 model = translation * rotation * scaleMat;
	//model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));

	glm::vec3 upDir = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 camPos = glm::vec3(0.0f, 0.0f, -5.0f);
	glm::vec3 lookDir = glm::normalize(camPos - glm::vec3(0.1f, 0.1f, 0.1f));

	glm::mat4 view = glm::lookAt(camPos, camPos + lookDir, upDir);

	// note that we're translating the scene in the reverse direction of where we want to move
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	//projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	projection = glm::ortho(0.0f, 800.0f, 800.0f, 0.0f, 0.1f, 100.0f);

	

	while (!glfwWindowShouldClose(window)) {
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		shader.use();
		int modelLoc = glGetUniformLocation(shader.ID, "model");
		int viewLoc = glGetUniformLocation(shader.ID, "view");
		int projectionLoc = glGetUniformLocation(shader.ID, "projection");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(VAO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glUseProgram(0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}
	// Delete Window
	glfwDestroyWindow(window);
	//Terminate GLFW
	glfwTerminate();
}