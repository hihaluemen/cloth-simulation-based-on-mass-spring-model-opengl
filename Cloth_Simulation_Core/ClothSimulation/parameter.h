#pragma once
#include "stdafx.h"

class Parameters {
public:
	Parameters();
	void resetFixedPoints();
	
	std::string imageTexturePath = "textures/texture.jpg";

	int iterationNumber = 30;

	GLfloat fixedPoints[100];
	GLfloat fixedPointsCopy[100];

	float Damping = -0.0089f;
	float KsStruct = 50.75f, KdStruct = -0.25f;
	float KsShear = 50.75f, KdShear = -0.25f;
	float KsBend = 50.95f, KdBend = -0.25f;
	float Mass = 1.0f;
	float TimeStep = 0.06;
	glm::vec3 Wind = glm::vec3(0.0f);
	bool ifWind = false;
	glm::vec3 Gravity = glm::vec3(0.0f, -0.00981f, 0.0f);
	glm::vec3 LightColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
};