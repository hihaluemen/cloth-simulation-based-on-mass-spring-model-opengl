#pragma once
#include "stdafx.h"
#include "parameter.h"
#include "model.h"
#include "simulation.h"

class TweakUI {
public:
	TweakUI();
	void bindSimulation(Simulation *simulation);
	Simulation *getSimulation();
	void initUIFunction();
	void drawUI();
	void startOrPause(void *clientData);
	void ifFillTexture(void *clientData);
	void ifWind(void *clientData);
	void reset(void *clientData);

private:
	Simulation *simulation;
};