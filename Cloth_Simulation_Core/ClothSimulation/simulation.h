#pragma once
#include "stdafx.h"
#include "model.h"
#include "camera.h"
#include "shaders.h"
#include "parameter.h"

class Simulation {
public:
	void bindModel(Model *model);
	void bindShaders(Shaders *shaders);
	void bindCamera(Camera *camera);
	void bindParameters(Parameters *parameters);
	void drawFloor();
	void simulation();
	Model *getModel();
	Parameters *getParameters();
	Shaders *getShaders();

	bool running = false;
	bool ifFill = false;
private:
	void simulationRender();
	void textureAndLightRender();
	void setOrthoGraphicProjection();
	void resetPerspectiveProjection();

	Model * model;
	Camera *camera;
	Shaders *shaders;
	Parameters *parameters;
};