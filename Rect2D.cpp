#include"Rect2D.h"
#include <glm/glm/gtx/string_cast.hpp>






Rect2D::Rect2D() : Rect2D(glm::vec3(1.0), glm::vec3(1.0), glm::vec3(1.0)) {};

Rect2D::Rect2D(glm::vec3 scale, glm::vec3 color, glm::vec3 pos) {
	this->isTextured = false;
	GLfloat vertexAndColorArray[] = {
	// positions         // colors
	 1.0f,  1.0f, 0.0f,  color[0], color[1], color[2],  // top right
	 1.0f, -1.0f, 0.0f,  color[0], color[1], color[2],  // bottom right
	-1.0f, -1.0f, 0.0f,  color[0], color[1], color[2],  // bottom left
	-1.0f,  1.0f, 0.0f,  color[0], color[1], color[2],  // top left 
	};

	this->vertices.assign(vertexAndColorArray, vertexAndColorArray + _countof(vertexAndColorArray));
	this->vertices.shrink_to_fit();
	/*if (false) {
		for (auto i : vertices) {
			std::cout << i << std::endl;
		}
		std::cout << "----------" << std::endl << this->vertices.size() * sizeof(GLfloat) << "vacarray size = " << sizeof(vertexAndColorArray) << std::endl << std::endl;
		std::cout << "----------" << std::endl << this->vertices.data()[23] << std::endl<< "vacarray first object = " << vertexAndColorArray[23] << std::endl << std::endl;
	}*/
	this->color = color;

	this->indices = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

	this->pos = glm::vec3(-pos[0], pos[1], pos[2]);

	this->scale = scale;

	this->firstDrawCall = true;

	this->textureID = 1;

	std::cout << pos[0] << std::endl;

	glGenVertexArrays(1, &this->RectVAO);
	glBindVertexArray(this->RectVAO);

	glGenBuffers(1, &this->RectVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->RectVBO);


	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertexAndColorArray), vertexAndColorArray, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(GLfloat), this->vertices.data(), GL_STATIC_DRAW);

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

//constructor for textured Rect2D
Rect2D::Rect2D(glm::vec3 scale, const char* texture, glm::vec3 pos) {

	this->isTextured = true;

	//using texture image, generate texture
	int tWidth, tHeight, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	this->textureData = stbi_load(texture, &tWidth, &tHeight, &nrChannels, 0); //load image

	

	this->color = glm::vec3(0.2f, 0.1f, 0.4f);

	GLfloat vertexAndColorArray[] = {
	// positions         // colors                                       // texture coords
	 1.0f,  1.0f, 0.0f,  this->color[0], this->color[1], this->color[2], 1.0f, 1.0f, // top right
	 1.0f, -1.0f, 0.0f,  this->color[0], this->color[1], this->color[2], 1.0f, 0.0f, // bottom right
	-1.0f, -1.0f, 0.0f,  this->color[0], this->color[1], this->color[2], 0.0f, 0.0f, // bottom left
	-1.0f,  1.0f, 0.0f,  this->color[0], this->color[1], this->color[2], 0.0f, 1.0f // top left 
	};
	
	this->vertices.assign(vertexAndColorArray, vertexAndColorArray + _countof(vertexAndColorArray));
	this->vertices.shrink_to_fit();

	if (true) {
		for (auto i : vertices) {
			std::cout << i << std::endl;
		}
		std::cout << "----------" << std::endl << this->vertices.size() * sizeof(GLfloat) << "vacarray size = " << sizeof(vertexAndColorArray) << std::endl << std::endl;
		std::cout << "----------" << std::endl << this->vertices.data()[0] << std::endl << "vacarray first object = " << vertexAndColorArray[0] << std::endl << std::endl;
	}
	this->color = color;


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

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat), this->vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &this->RectEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->RectEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices), this->indices.data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	

	//texture generation
	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (this->textureData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, this->textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Texture Loaded" << std::endl;
		std::cout << (unsigned int) this->textureData[0] << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	//free image data memory
	stbi_image_free(this->textureData);

	


	

	glBindVertexArray(0);
}

Rect2D::Rect2D(glm::vec3 scale, cellularAutomataPlayfield image, glm::vec3 pos) {

	this->isTextured = true;

	//using texture image, generate texture
	int tWidth, tHeight, nrChannels;
	tWidth = image.getWidth();
	tHeight = image.getHeight();
	nrChannels = 3;

	stbi_set_flip_vertically_on_load(true);
	std::vector<glm::vec3> pfc = image.getPlayfieldColors();
	this->textureDataVec3 = pfc.data();



	this->color = glm::vec3(0.2f, 0.1f, 0.4f);

	GLfloat vertexAndColorArray[] = {
		// positions         // colors                                       // texture coords
		 1.0f,  1.0f, 0.0f,  this->color[0], this->color[1], this->color[2], 1.0f, 1.0f, // top right
		 1.0f, -1.0f, 0.0f,  this->color[0], this->color[1], this->color[2], 1.0f, 0.0f, // bottom right
		-1.0f, -1.0f, 0.0f,  this->color[0], this->color[1], this->color[2], 0.0f, 0.0f, // bottom left
		-1.0f,  1.0f, 0.0f,  this->color[0], this->color[1], this->color[2], 0.0f, 1.0f // top left 
	};

	this->vertices.assign(vertexAndColorArray, vertexAndColorArray + _countof(vertexAndColorArray));
	this->vertices.shrink_to_fit();

	if (true) {
		for (auto i : vertices) {
			std::cout << i << std::endl;
		}
		std::cout << "----------" << std::endl << this->vertices.size() * sizeof(GLfloat) << "vacarray size = " << sizeof(vertexAndColorArray) << std::endl << std::endl;
		std::cout << "----------" << std::endl << this->vertices.data()[0] << std::endl << "vacarray first object = " << vertexAndColorArray[0] << std::endl << std::endl;
	}
	this->color = color;


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

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat), this->vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &this->RectEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->RectEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices), this->indices.data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);



	//texture generation
	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (this->textureDataVec3)
	{
		//glPixelStoref(GL_UNPACK_ROW_LENGTH, tWidth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_RGB, GL_FLOAT, this->textureDataVec3);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Texture Loaded" << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}




	glBindVertexArray(0);
}


std::vector<GLfloat> Rect2D::getVertices()
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
	

	/*
	* a lambda function which straight up doesn't work and idk why. meant to replace identical code in draw binds below.
	* if anyone can work out why this doesn't work i will love u forever
	* -cam
	* 
	auto bindArrayAndDrawElements = [this]() -> void {
		glBindVertexArray(this->RectVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	};
	*/

	if (this->isTextured) //if this is a textured rect, use the texture in the shader call
	{
		
		glUniform1i(glGetUniformLocation(shader.ID, "textureExists"), true);
		glBindTexture(GL_TEXTURE_2D, this->textureID);
		glBindVertexArray(this->RectVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glUniform1i(glGetUniformLocation(shader.ID, "textureExists"), false);
	}
	else //otherwise just draw normally (with color)
	{
		glUniform1i(glGetUniformLocation(shader.ID, "textureExists"), false);
		glBindVertexArray(this->RectVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->RectEBO);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	

	glBindVertexArray(0);
}