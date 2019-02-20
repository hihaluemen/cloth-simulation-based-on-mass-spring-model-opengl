#pragma once
#include "stdafx.h"

class Model {
public:
	Model();
	void loadParticles();
	void initModel(float width, float height, int clothWidth, int clothHeight, float angle, glm::vec4 center);

	float width = 0.0, height = 0.0, angle = 0.0, pi = 3.1415926;
	int clothWidth = 0, clothHeight = 0, totalParticles = 0;
	glm::vec4 center, *positions, *prevPositions;
};