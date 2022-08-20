#ifndef RECT_2D
#define RECT_2D
#include<array>
#include<glm/glm/glm.hpp>
#include<GLFW/glfw3.h>

class Rect2D
{
public:
	//int ID;
	Rect2D(int size, glm::vec3 color, glm::vec3 pos);
	GLfloat vertices[24] = {
	 1.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  // top right
	 1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right
	-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  // bottom left
	-1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f  // top left 
	};
	GLuint indices[6] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	std::array<GLfloat, 24> getVertices();
	glm::vec3 getPosition();
protected:
	std::array<GLfloat, 24> vertices2;
	glm::vec3 pos;

};



#endif