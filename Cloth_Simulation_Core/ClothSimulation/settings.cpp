#include "stdafx.h"
#include "settings.h"

void LoadSettings::loadSettings() {
	int indexAttribute = -1;
	std::string line;
	std::ifstream fs("settings/settings.option");
	while (std::getline(fs, line)) {
		indexAttribute += 1;
		if (indexAttribute == 0) {
			std::stringstream converter;
			converter << line;
			converter >> this->clothWidth;
			converter.clear();
			//std::cout << this->clothWidth << std::endl;
		}
		if (indexAttribute == 1) {
			std::stringstream converter;
			converter << line;
			converter >> this->clothHeight;
			converter.clear();
			//std::cout << this->clothHeight << std::endl;
		}
		if (indexAttribute == 2) {
			std::stringstream converter;
			converter << line;
			converter >> this->width;
			converter.clear();
			//std::cout << this->width << std::endl;
		}
		if (indexAttribute == 3) {
			std::stringstream converter;
			converter << line;
			converter >> this->height;
			converter.clear();
			//std::cout << this->height << std::endl;
		}
		if (indexAttribute == 4 || indexAttribute == 5 || indexAttribute == 6 || indexAttribute == 7) {
			std::stringstream converter;
			converter << line;
			converter >> this->fixedPoints[indexAttribute - 4];
			//std::cout << this->fixedPoints[indexAttribute - 4] << std::endl;
			converter.clear();
		}
		if (indexAttribute == 8) {
			this->imagePath = line;
			//std::cout << this->imagePath << std::endl;
			break;
		}
	}
	fs.close();
}

void LoadSettings::bindParameters(Parameters *parameters) {
	this->parameters = parameters;
}