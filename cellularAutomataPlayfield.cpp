#include "cellularAutomataPlayfield.h"
#include <glad/gl.h>

cellularAutomataPlayfield::cellularAutomataPlayfield(int width, int height, glm::vec3 alive, glm::vec3 dead, bool randomInitialState)
{

	srand((unsigned)time(NULL));
	this->width = width;
	this->height = height;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			glm::vec3 color;
			if (randomInitialState) {
				float randomNumber = (float)rand() / RAND_MAX;
				color = (randomNumber > 0.5) ? alive : dead;
			}
			else {
				color = dead;
			}

			this->playfieldA.push_back(color);
			this->playfieldB.push_back(color);
		}

	}
	this->playfieldA.shrink_to_fit();
	this->playfieldBackBuffer = this->playfieldB;
	this->playfieldFrontBuffer = this->playfieldA;
}

std::vector<glm::vec3> cellularAutomataPlayfield::getPlayfieldColors() {
	return this->playfieldFrontBuffer;
}

int cellularAutomataPlayfield::getWidth()
{
	return this->width;
}

int cellularAutomataPlayfield::getHeight()
{
	return this->height;
}

glm::vec3 cellularAutomataPlayfield::getPoint(int x, int y)
{
	if (this->isInBounds(x, y)) {
		int index = x + this->width * y;
		return this->playfieldFrontBuffer[index];
	}
	else {
		throw std::invalid_argument("You tried to get a point that doesn't exist! (Not in Bounds)");
	}

}



void cellularAutomataPlayfield::setPoint(int x, int y, glm::vec3 newValue)
{
	if (this->isInBounds(x, y)) {
		int index = x + this->width * y;
		this->playfieldBackBuffer[index] = newValue;
	}
	else {
		throw std::invalid_argument("You tried to set a point that doesn't exist! (Not in Bounds)");
	}
}

bool cellularAutomataPlayfield::isInBounds(int x, int y) {
	if (x >= 0 && y >= 0 && x < this->width && y < this->height) {
		return true;
	}
	return false;
}

bool cellularAutomataPlayfield::hasUpdated() {
	return this->updated;
}

void cellularAutomataPlayfield::setUpdated(bool u) {
	this->updated = u;
}

void cellularAutomataPlayfield::updateSimulation(glm::vec3 alive, glm::vec3 dead)
{
	glFinish();
	int total = 0;
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			int r = this->getNeighbourTotal(i, j, alive, dead);
			/*if (r > 0)
			{
				std::cout << i << ", " << j << " total = " << r << std::endl;
			}*/
			total = total + r;
		}
	}
	this->swapPlayfieldBuffers();
	//std::cout << total << std::endl;
}

void cellularAutomataPlayfield::swapPlayfieldBuffers() {
	std::swap(this->playfieldFrontBuffer, this->playfieldBackBuffer);
}

int cellularAutomataPlayfield::getNeighbourTotal(int x, int y, glm::vec3 alive, glm::vec3 dead) {
	int ret = 0;
	if (!this->isInBounds(x, y)) return -1 ;
	//top left
	if (this->isInBounds(x - 1, y + 1)) {
		if (this->playfieldFrontBuffer[(x - 1) + this->width * (y + 1)] == alive) {
			ret++;
		}
	}
	//top middle
	if (this->isInBounds(x, y + 1)) {
		if (this->playfieldFrontBuffer[x + this->width * (y + 1)] == alive) {
			ret++;
		}
	}
	//top right
	if (this->isInBounds(x + 1, y + 1)) {
		if (this->playfieldFrontBuffer[x + 1 + this->width * (y + 1)] == alive) {
			ret++;
		}
	}
	//middle left
	if (this->isInBounds(x - 1, y)) {
		if (this->playfieldFrontBuffer[(x - 1) + this->width * (y)] == alive) {
			ret++;
		}
	}
	//middle
	if (this->playfieldFrontBuffer[x + this->width * (y)] == alive) {
		ret++;
	}

	//middle right
	if (this->isInBounds(x + 1, y)) {
		if (this->playfieldFrontBuffer[x + 1 + this->width * y] == alive) {
			ret++;
		}
	}

	//bottom left
	if (this->isInBounds(x - 1, y - 1)) {
		if (this->playfieldFrontBuffer[(x - 1) + this->width * (y - 1)] == alive) {
			ret++;
		}
	}
	//bottom middle
	if (this->isInBounds(x, y - 1)) {
		if (this->playfieldFrontBuffer[x + this->width * (y - 1)] == alive) {
			ret++;
		}
	}
	//bottom right
	if (this->isInBounds(x + 1, y - 1)) {
		if (this->playfieldFrontBuffer[x + 1 + this->width * (y - 1)] == alive) {
			ret++;
		}
	}

	if (ret == 3) {
		this->setPoint(x, y, alive);
		this->updated = true;
		return ret;
	}

	else if (ret == 4) {
		this->setPoint(x, y, this->getPoint(x,y));
		return ret;
	}
	else {
		this->setPoint(x, y, dead);
		this->updated = true;
		return ret;
	}
	return ret;
}




void cellularAutomataPlayfield::printSize() {
	int c = 0;
	for (auto i : this->playfieldFrontBuffer) {
		std::cout << i.r << std::endl;
		++c;
		if (c >= 1600) {
			break;
		}
	}
}
