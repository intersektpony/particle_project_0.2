#ifndef RECT_2D
#define RECT_2D
#define GLFW_INCLUDE_NONE
#include <iostream>
#include<array>
#include<glm/glm/glm.hpp>
#include<GLFW/glfw3.h>
#include"shaderClass.h"
#include<glm/glm/gtc/matrix_transform.hpp>
#include<glm/glm/gtc/type_ptr.hpp>
class Rect2D
{
public:
	//int ID;
	Rect2D();

	Rect2D(glm::vec3 scale, glm::vec3 color, glm::vec3 pos);
	//GLfloat vertices[24] = {
	// 1.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  // top right
	// 1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right
	//-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  // bottom left
	//-1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f  // top left 
	//};
	GLuint indices2[6] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	std::array<GLfloat, 24> getVertices();
	glm::vec3 getPosition();
	void setPosition(glm::vec3 newPosition);

	void Draw(Shader shader, glm::mat4 view, glm::mat4 proj);
protected:
	std::array<GLfloat, 24> vertices;
	std::array<GLuint, 6> indices;
	glm::vec3 pos;
	glm::vec3 scale;
	glm::vec3 color;

	GLuint RectVAO;
	GLuint RectVBO;
	GLuint RectEBO;

	bool firstDrawCall;

};



#endif