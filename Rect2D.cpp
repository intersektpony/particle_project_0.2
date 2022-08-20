#include"Rect2D.h"
#include <iostream>
#include <array>

Rect2D::Rect2D(int size, glm::vec3 color, glm::vec3 pos) {
	this->vertices2 = {
	 1.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  // top right
	 1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom right
	-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  // bottom left
	-1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f  // top left 
	};

	this->pos = glm::vec3(-pos[0], pos[1], pos[2]);
	std::cout << pos[0] << std::endl;
}
std::array<GLfloat, 24> Rect2D::getVertices()
{
	return this->vertices2;
}

glm::vec3 Rect2D::getPosition()
{
	return this->pos;
}