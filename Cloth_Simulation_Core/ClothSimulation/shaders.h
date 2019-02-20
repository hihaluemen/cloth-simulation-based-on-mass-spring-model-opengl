#pragma once
#include "model.h"
#include "stdafx.h"
#include "parameter.h"
#include "glslshader.h"

class Shaders {
public:
	void createFBOAndTextures();
	void initializeFBO();
	void loadShaders();
	void bindModel(Model *model);
	void bindParameters(Parameters *parameters);

	GLSLShader shadersGroup[3];
	GLuint fboGroup[2], texturesGroup[6];
	int readHandler = 0, writeHandler = 1;
	GLenum mrt[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2 };
private:
	Model *model;
	Parameters *parameters;
};