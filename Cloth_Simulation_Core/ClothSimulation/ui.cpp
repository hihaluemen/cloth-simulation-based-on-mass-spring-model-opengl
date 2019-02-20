#include "stdafx.h"
#include "ui.h"

TweakUI::TweakUI() {
	
}

void TweakUI::bindSimulation(Simulation *simulation) {
	this->simulation = simulation;
}

void TweakUI::drawUI() {
	TwDraw();
}

Simulation * TweakUI::getSimulation() {
	return this->simulation;
}

void TweakUI::initUIFunction() {
	glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
	glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	//glutKeyboardFunc((GLUTkeyboardfun)TwEventKeyboardGLUT);
	glutSpecialFunc((GLUTspecialfun)TwEventSpecialGLUT);
	TwGLUTModifiersFunc(glutGetModifiers);
}

void TweakUI::ifWind(void *clientData) {
	if (this->simulation->getParameters()->ifWind == true) {
		this->simulation->getParameters()->ifWind = false;
	}
	else {
		this->simulation->getParameters()->ifWind = true;
	}
}

void TweakUI::startOrPause(void *clientData) {
	if (simulation->running == true) {
		simulation->running = false;
	}
	else {
		simulation->running = true;
	}
}

void TweakUI::ifFillTexture(void *clientData) {
	if (simulation->ifFill == true) {
		simulation->ifFill = false;
	}
	else {
		simulation->ifFill = true;
	}
}

void TweakUI::reset(void *clientData) {
	this->simulation->getModel()->loadParticles();
	this->simulation->getShaders()->initializeFBO();
}