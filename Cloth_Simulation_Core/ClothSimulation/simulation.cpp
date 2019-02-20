#include "stdafx.h"
#include "simulation.h"

void Simulation::bindModel(Model *model) {
	this->model = model;
}

void Simulation::bindShaders(Shaders *shaders) {
	this->shaders = shaders;
}

void Simulation::bindParameters(Parameters *parameters) {
	this->parameters = parameters;
}

void Simulation::bindCamera(Camera *camera) {
	this->camera = camera;
}

Model *Simulation::getModel() {
	return this->model;
}

Shaders *Simulation::getShaders() {
	return this->shaders;
}

Parameters *Simulation::getParameters() {
	return this->parameters;
}

void Simulation::drawFloor() {
	glBegin(GL_LINES);
	glColor3f(0.5f, 0.5f, 0.5f);
	for (int i = -50; i <= 50; i++)
	{
		glVertex3f((float)i, -10, (float)-50);
		glVertex3f((float)i, -10, (float)50);

		glVertex3f((float)-50, -10, (float)i);
		glVertex3f((float)50, -10, (float)i);
	}
	glEnd();
}

void Simulation::textureAndLightRender() {
	glBegin(GL_QUADS);
	for (int h = 1; h < model->clothHeight; h++) {
		for (int w = 0; w < model->clothWidth - 1; w++) {
			glVertex2f(float(h) / (model->clothHeight - 1), float(w) / (model->clothWidth - 1));
			glVertex2f(float(h - 1) / (model->clothHeight - 1), float(w) / (model->clothWidth - 1));
			glVertex2f(float(h - 1) / (model->clothHeight - 1), float(w + 1) / (model->clothWidth - 1));
			glVertex2f(float(h) / (model->clothHeight - 1), float(w + 1) / (model->clothWidth - 1));
		}
	}
	glEnd();
}

void Simulation::simulationRender() {
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(1, 0);
	glVertex2f(1, 1);
	glVertex2f(0, 1);
	glEnd();
}

void Simulation::setOrthoGraphicProjection() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void Simulation::resetPerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Simulation::simulation() {
	setOrthoGraphicProjection();
	glViewport(0, 0, model->clothWidth, model->clothHeight);
	for (int i = 0; i < parameters->iterationNumber; i++) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, shaders->fboGroup[shaders->writeHandler]);
		glDrawBuffers(3, shaders->mrt);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, shaders->texturesGroup[3 * (shaders->readHandler)]);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, shaders->texturesGroup[3 * (shaders->readHandler) + 1]);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, shaders->texturesGroup[3 * (shaders->readHandler) + 2]);

		glClear(GL_COLOR_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		srand(time(NULL));

		if (this->running == true) {
			shaders->shadersGroup[0].Use();
			glUniform1f(shaders->shadersGroup[0]("timeStep"), parameters->TimeStep);
			glUniform1fv(shaders->shadersGroup[0]("fixedPoints"), 100, &parameters->fixedPoints[0]);
			if (parameters->ifWind == true) {
				glUniform1f(shaders->shadersGroup[0]("windX"), (2 * float(rand()) / RAND_MAX - 1.0)*0.000);
				glUniform1f(shaders->shadersGroup[0]("windY"), (2 * float(rand()) / RAND_MAX - 1.0)*0.000);
				glUniform1f(shaders->shadersGroup[0]("windZ"), (2 * float(rand()) / RAND_MAX - 1.0)*0.004);
			}
			simulationRender();
			shaders->shadersGroup[0].UnUse();

			int tempHandler = shaders->readHandler;
			shaders->readHandler = shaders->writeHandler;
			shaders->writeHandler = tempHandler;
		}
	}
	resetPerspectiveProjection();

	glReadBuffer(GL_NONE);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glReadBuffer(GL_BACK);
	glDrawBuffer(GL_BACK);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glViewport(0, 0, camera->getWindowsWidth(), camera->getWindowsHeight());

	if (this->ifFill) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	shaders->shadersGroup[1].Use();
	//glUniform3f(shaders->shadersGroup[1]("lightColor"), parameters->LightColor.x, parameters->LightColor.y, parameters->LightColor.z);
	glUniform3f(shaders->shadersGroup[1]("cameraPosition"), camera->getCameraPosition().x, camera->getCameraPosition().y, camera->getCameraPosition().z);
	glUniform1i(shaders->shadersGroup[1]("map"), 0);
	glUniform1i(shaders->shadersGroup[1]("tex"), 2);
	textureAndLightRender();
	shaders->shadersGroup[1].UnUse();
}