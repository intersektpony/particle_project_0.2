#pragma once
#include<iostream>
#include <array>
#include <glm/glm/glm.hpp>
#include <vector>

class cellularAutomataPlayfield {
public:
	cellularAutomataPlayfield(int width, int height);
	void printSize();
	std::vector<glm::vec3> getPlayfieldColors();
	int getWidth(), getHeight();
	glm::vec3 getPoint(int x, int y);
	void setPoint(int x, int y, glm::vec3 newValue);
	int getNeighbourTotal(int x, int y, glm::vec3 goalTest);


protected:
	int width, height;
	std::vector<glm::vec3> playfield = {};
	//std::vector<glm::vec3> playfield = {};
	std::vector<unsigned int> oneDimensionalPlayfield;

};