#include "stdafx.h"
#include "model.h"

Model::Model() {

}

void Model::initModel(float width, float height, int clothWidth, int clothHeight, float angle, glm::vec4 center) {
	this->width = width, this->height = height;
	this->clothWidth = clothWidth, this->clothHeight = clothHeight, this->totalParticles = clothHeight * clothWidth;
	this->center = center, this->angle = angle;
	this->positions = new glm::vec4[this->totalParticles];
	this->prevPositions = new glm::vec4[this->totalParticles];
}

void Model::loadParticles() {
	int index = 0;
	float helpSize = width / 2.0f;
	for (int j = 0; j <= clothHeight - 1; j++) {
		for (int i = 0; i <= clothWidth - 1; i++) {
			positions[index] = glm::vec4(((float(i) / (clothWidth - 1)) * 2 - 1) * helpSize, helpSize, ((float(j) / (clothHeight - 1)) * height), 1);
			prevPositions[index] = positions[index];
			index += 1;
		}
	}
}