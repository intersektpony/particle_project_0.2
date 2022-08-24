#include "cellularAutomataPlayfield.h"

cellularAutomataPlayfield::cellularAutomataPlayfield(int width, int height)
{
	//this->playfieldA.reserve(width * height);
	this->width = width;
	this->height = height;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			/*switch (y % 4) {
				case 0:
					this->playfieldA.push_back(glm::vec3(0.5f, 0.0f, 0.0f));
					break;
			
				case 1:
					this->playfieldA.push_back(glm::vec3(0.0f, 0.5f, 0.0f));
					break;
			
				case 2:
					this->playfieldA.push_back(glm::vec3(1.0f, 0.0f, 0.5f));
					break;
			
				case 3:
					this->playfieldA.push_back(glm::vec3(1.0f, 1.5f, 0.5f));
					break;
			}*/
			this->playfieldA.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
			this->playfieldB.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
			//this->playfieldA.push_back(glm::vec3(0.5f, 0.0f, 0.0f));
			//(i+j)/(width/height)
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
	int index = x + this->width * y;
	return this->playfieldFrontBuffer[index];
}

void cellularAutomataPlayfield::setPoint(int x, int y, glm::vec3 newValue)
{
	int index = x + this->width * y;
	this->playfieldBackBuffer[index] = newValue;
}

int cellularAutomataPlayfield::getNeighbourTotal(int x, int y, glm::vec3 goalTest) {
	int ret = 0;

	//top left
	if (x - 1 > 0 && y + 1 < this -> height) {
		if (this->playfieldFrontBuffer[(x - 1) + this->width * (y + 1)] == goalTest) {
			ret++;
		}
	}
	//top middle
	if (y + 1 < this->height) {
		if (this->playfieldFrontBuffer[x + this->width * (y + 1)] == goalTest) {
			ret++;
		}
	}
	//top right
	if (x + 1 < this->width && y + 1 < this->height) {
		if (this->playfieldFrontBuffer[x + 1 + this->width * (y + 1)] == goalTest) {
			ret++;
		}
	}
	//middle left
	if (x - 1 > 0) {
		if (this->playfieldFrontBuffer[(x - 1) + this->width * (y)] == goalTest) {
			ret++;
		}
	}
	//middle
	if (this->playfieldFrontBuffer[x + this->width * (y)] == goalTest) {
		ret++;
	}

	//middle right
	if (x + 1 < this->width) {
		if (this->playfieldFrontBuffer[x + 1 + this->width * y] == goalTest) {
			ret++;
		}
	}

	//bottom left
	if (x - 1 > 0 && y - 1 > 0) {
		if (this->playfieldFrontBuffer[(x - 1) + this->width * (y - 1)] == goalTest) {
			ret++;
		}
	}
	//bottom middle
	if (y - 1 > 0) {
		if (this->playfieldFrontBuffer[x + this->width * (y - 1)] == goalTest) {
			ret++;
		}
	}
	//bottom right
	if (x + 1 < this->width && y - 1 > 0) {
		if (this->playfieldFrontBuffer[x + 1 + this->width * (y - 1)] == goalTest) {
			ret++;
		}
	}

	if (ret <= 3) {
		this->playfieldBackBuffer[x + this->width * (y)] = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	else if (ret > 4) {
		this->playfieldBackBuffer[x + this->width * (y)] = goalTest;
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
