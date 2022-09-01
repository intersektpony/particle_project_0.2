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
#include <vector>
#include <stb/stb_image.h>
#include "cellularAutomataPlayfield.h"
class Rect2D
{
public:
	//int ID;
	Rect2D();

	Rect2D(glm::vec3 scale, glm::vec3 color, glm::vec3 pos);

	Rect2D(glm::vec3 scale, const char* textureImage, glm::vec3 pos);
	//Rect2D(glm::vec3 scale, std::array<std::array<glm::vec3>> textureImage, glm::vec3 pos);
	Rect2D(glm::vec3 scale, cellularAutomataPlayfield image, glm::vec3 pos);

	/*GLuint indices2[6] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};*/
	std::vector<GLfloat> getVertices();
	glm::vec3 getPosition();
	void setPosition(glm::vec3 newPosition);
	void updateTexture(cellularAutomataPlayfield image);

	void Draw(Shader shader, glm::mat4 view, glm::mat4 proj);
protected:
	std::vector<GLfloat> vertices;
	std::array<GLuint, 6> indices;
	glm::vec3 pos;
	glm::vec3 scale;
	glm::vec3 color;
	unsigned char* textureData;
	glm::vec3* textureDataVec3;
	bool isTextured = false;

	GLuint RectVAO;
	GLuint RectVBO;
	GLuint RectEBO;
	unsigned int textureID;

	bool firstDrawCall = true;

};



#endif