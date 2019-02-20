#include "stdafx.h"
#include "camera.h"

Camera::Camera() {}
void Camera::mouseClick(int button, int state, int x, int y) {
	if (state == GLUT_DOWN)
		oldMousePosition.x = x, oldMousePosition.y = y;
}

void Camera::mouseWheel(int button, int direction, int x, int y) {
	if (direction > 0) {
		cameraRadius += 10.0;
	}
	else {
		if (cameraRadius < 20.0)
			return;
		cameraRadius -= 10.0;
	}
}

void Camera::mouseMove(int x, int y) {
	cameraAngle += x - oldMousePosition.x;
	cameraHeight += y - oldMousePosition.y;
	oldMousePosition.x = x, oldMousePosition.y = y;
}

void Camera::windowsReshape(int w, int h) {
	windowsWidth = w, windowsHeight = h;
	glViewport(0, 0, windowsWidth, windowsHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0f, (float)windowsWidth / windowsHeight, 1.0f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
}

void Camera::keyboardPush(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'w': {
		if (cameraHeight < 500.0)
			cameraHeight += 1.2;
	}break;
	case 's': {
		if (cameraHeight > -500.0)
			cameraHeight -= 1.2;
	}break;
	case 'a': {
		cameraAngle += 5.0;
	}break;
	case 'd': {
		cameraAngle -= 5.0;
	}break;
	default:
		break;
	}
}

glm::vec3 Camera::getCameraPosition() {
	return glm::vec3(cameraRadius*cos(radian*cameraAngle), cameraHeight, cameraRadius*sin(radian*cameraAngle));
}

float Camera::getWindowsWidth() {
	return this->windowsWidth;
}

float Camera::getWindowsHeight() {
	return this->windowsHeight;
}

void Camera::openGLFunctionInit() {
	
}