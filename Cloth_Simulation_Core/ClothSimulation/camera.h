#pragma once
#include "stdafx.h"

class Camera {
public:
	Camera();
	void mouseClick(int button, int state, int x, int y);
	void mouseWheel(int button, int direction, int x, int y);
	void mouseMove(int x, int y);
	void windowsReshape(int w, int h);
	void keyboardPush(unsigned char key, int x, int y);
	void openGLFunctionInit();
	glm::vec3 getCameraPosition();
	float getWindowsWidth();
	float getWindowsHeight();
private:
	const float radian = 3.1415926 / 180.0;
	float cameraAngle = 90.0;
	float cameraHeight = 0.0f;
	float windowsWidth = 600;
	float windowsHeight = 800;
	float cameraRadius = 50.0f;
	glm::vec2 oldMousePosition = glm::vec2(-1.0, -1.0);
};