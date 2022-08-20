#include"Rect2D.h"
#include <glm/glm/gtx/string_cast.hpp>



Rect2D::Rect2D() : Rect2D(glm::vec3(1.0), glm::vec3(1.0), glm::vec3(1.0)) {};

Rect2D::Rect2D(glm::vec3 scale, glm::vec3 color, glm::vec3 pos) {
	this->vertices = {
	 1.0f,  1.0f, 0.0f,  color[0], color[1], color[2],  // top right
	 1.0f, -1.0f, 0.0f,  color[0], color[1], color[2],  // bottom right
	-1.0f, -1.0f, 0.0f,  color[0], color[1], color[2],  // bottom left
	-1.0f,  1.0f, 0.0f,  color[0], color[1], color[2],  // top left 
	};

	this->indices = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

	this->pos = glm::vec3(-pos[0], pos[1], pos[2]);

	this->scale = scale;

	this->firstDrawCall = true;
	std::cout << pos[0] << std::endl;

	glGenVertexArrays(1, &this->RectVAO);
	glBindVertexArray(this->RectVAO);

	glGenBuffers(1, &this->RectVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->RectVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &this->RectEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->RectEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices), this->indices.data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}
std::array<GLfloat, 24> Rect2D::getVertices()
{
	return this->vertices;
}

glm::vec3 Rect2D::getPosition()
{
	return this->pos;
}

void Rect2D::setPosition(glm::vec3 newPosition)
{
	this->pos = newPosition;
}



void Rect2D::Draw(Shader shader, glm::mat4 view, glm::mat4 proj) {

	//std::cout << firstDrawCall << std::endl;

	glm::mat4 translation = glm::translate(glm::mat4(1.0), this->pos);
	glm::mat4 model = translation * glm::mat4(1.0f) * glm::scale(glm::mat4(1.0), this->scale);
	//calculate the MVP matrix on CPU side
	glm::mat4 mvp = proj * view * model;

	//debug stuff
	if (this->firstDrawCall == true) {
		std::cout << glm::to_string(model) << std::endl;
		this->firstDrawCall = false;
	}

	int mvpLoc = glGetUniformLocation(shader.ID, "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
	glBindVertexArray(this->RectVAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->RectEBO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}