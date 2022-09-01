#pragma once
#include<iostream>
#include <array>
#include <glm/glm/glm.hpp>
#include <vector>

/*defines a playfield for a cellular automata system.
* needs expanding to accomodate more complex objects and rules. 
*for now just excecutes conways GOL
*/

class cellularAutomataPlayfield {
public:
	cellularAutomataPlayfield(int width, int height, glm::vec3 alive, glm::vec3 dead, bool randomInitialState);
	cellularAutomataPlayfield(int width, int height);
	void printSize();
	std::vector<glm::vec3> getPlayfieldColors();
	int getWidth(), getHeight();
	glm::vec3 getPoint(int x, int y);
	void setPoint(int x, int y, glm::vec3 newValue);
	int getNeighbourTotal(int x, int y, glm::vec3 alive, glm::vec3 dead);
	void swapPlayfieldBuffers();
	bool isInBounds(int x, int y);
	bool hasUpdated();
	void setUpdated(bool u);
	void updateSimulation(glm::vec3 alive, glm::vec3 dead);
	


protected:
	int width, height;
	std::vector<glm::vec3> playfieldA = {};
	std::vector<glm::vec3> playfieldB = {};
	std::vector<glm::vec3> playfieldFrontBuffer;
	std::vector<glm::vec3> playfieldBackBuffer;
	//std::vector<glm::vec3> playfield = {};
	std::vector<unsigned int> oneDimensionalPlayfield;
	bool updated;

};