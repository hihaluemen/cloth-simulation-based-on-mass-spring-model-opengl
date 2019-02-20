#pragma once
#include "stdafx.h"
#include "parameter.h"

class LoadSettings {
public:
	void loadSettings();
	void bindParameters(Parameters *parameters);

	int clothWidth = 200;
	int clothHeight = 200;
	float width = 50.0f;
	float height = 50.0f;
	GLfloat fixedPoints[4] = { 0,199,39800,39999 };
	std::string imagePath = "textures/texture.jpg";
private:
	Parameters * parameters;
};