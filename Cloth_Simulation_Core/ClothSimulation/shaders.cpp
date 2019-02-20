#include "stdafx.h"
#include "shaders.h"

void Shaders::createFBOAndTextures() {
	glGenTextures(6, texturesGroup);
	glGenFramebuffers(2, fboGroup);
}

void Shaders::initializeFBO() {
	//fbo[0]
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboGroup[0]);

	//fbo[0]'s textures[0]
	glBindTexture(GL_TEXTURE_2D, texturesGroup[0]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, model->clothWidth, model->clothHeight, 0, GL_RGBA, GL_FLOAT, model->positions);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, mrt[0], GL_TEXTURE_2D, texturesGroup[0], 0);
	//fbo[0]'s textures[1]
	glBindTexture(GL_TEXTURE_2D, texturesGroup[1]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, model->clothWidth, model->clothHeight, 0, GL_RGBA, GL_FLOAT, model->prevPositions);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, mrt[1], GL_TEXTURE_2D, texturesGroup[1], 0);
	//fbo[0]'s textures[2]
	texturesGroup[2] = SOIL_load_OGL_texture(parameters->imageTexturePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texturesGroup[2]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, mrt[2], GL_TEXTURE_2D, texturesGroup[2], 0);

	//fbo[1]
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboGroup[1]);

	//fbo[1]'s textures[3]
	glBindTexture(GL_TEXTURE_2D, texturesGroup[3]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, model->clothWidth, model->clothHeight, 0, GL_RGBA, GL_FLOAT, model->positions);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, mrt[0], GL_TEXTURE_2D, texturesGroup[3], 0);
	//fbo[1]'s textures[4]
	glBindTexture(GL_TEXTURE_2D, texturesGroup[4]);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, model->clothWidth, model->clothHeight, 0, GL_RGBA, GL_FLOAT, model->prevPositions);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, mrt[1], GL_TEXTURE_2D, texturesGroup[4], 0);
	//fbo[1]'s textures[5]
	texturesGroup[5] = SOIL_load_OGL_texture(parameters->imageTexturePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texturesGroup[5]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, mrt[2], GL_TEXTURE_2D, texturesGroup[5], 0);

	GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if (status == GL_FRAMEBUFFER_COMPLETE) {
		cout << "FBO setup succeeded." << endl;
	}
	else {
		cout << "Problem with FBO setup." << endl;
	}

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Shaders::loadShaders() {
	shadersGroup[0].LoadFromFile(GL_VERTEX_SHADER, "shaders/simulation.vert");
	shadersGroup[0].LoadFromFile(GL_FRAGMENT_SHADER, "shaders/simulation.frag");
	shadersGroup[0].CreateAndLinkProgram();
	shadersGroup[0].Use();
	shadersGroup[0].AddUniform("fixedPoints");				glUniform1fv(shadersGroup[0]("fixedPoints"), 100, &parameters->fixedPoints[0]);
	shadersGroup[0].AddUniform("positions");				glUniform1i(shadersGroup[0]("positions"), 0);
	shadersGroup[0].AddUniform("prevPositions");			glUniform1i(shadersGroup[0]("prevPositions"), 1);
	shadersGroup[0].AddUniform("DAMPING");					glUniform1f(shadersGroup[0]("DAMPING"), parameters->Damping);
	shadersGroup[0].AddUniform("MASS");						glUniform1f(shadersGroup[0]("MASS"), parameters->Mass);
	shadersGroup[0].AddUniform("timeStep");					glUniform1f(shadersGroup[0]("timeStep"), parameters->TimeStep);
	shadersGroup[0].AddUniform("KsStruct");					glUniform1f(shadersGroup[0]("KsStruct"), parameters->KsStruct);
	shadersGroup[0].AddUniform("KdStruct");					glUniform1f(shadersGroup[0]("KdStruct"), parameters->KdStruct);
	shadersGroup[0].AddUniform("KsShear");					glUniform1f(shadersGroup[0]("KsShear"), parameters->KsShear);
	shadersGroup[0].AddUniform("KdShear");					glUniform1f(shadersGroup[0]("KdShear"), parameters->KdShear);
	shadersGroup[0].AddUniform("KsBend");					glUniform1f(shadersGroup[0]("KsBend"), parameters->KsBend);
	shadersGroup[0].AddUniform("KdBend");					glUniform1f(shadersGroup[0]("KdBend"), parameters->KdBend);
	shadersGroup[0].AddUniform("GRAVITY");					glUniform3fv(shadersGroup[0]("GRAVITY"), 1, &parameters->Gravity.x);
	shadersGroup[0].AddUniform("clothTextureWidth");		glUniform1f(shadersGroup[0]("clothTextureWidth"), model->clothWidth);
	shadersGroup[0].AddUniform("clothTextureHeight");		glUniform1f(shadersGroup[0]("clothTextureHeight"), model->clothHeight);
	shadersGroup[0].AddUniform("realDistanceOfXandY");		glUniform2f(shadersGroup[0]("realDistanceOfXandY"), float(model->width) / (model->clothWidth - 1), float(model->height) / (model->clothHeight - 1));
	shadersGroup[0].AddUniform("textureDistanceOfXandY");	glUniform2f(shadersGroup[0]("textureDistanceOfXandY"), 1.0f / (model->clothWidth - 1), 1.0f / (model->clothHeight - 1));
	shadersGroup[0].AddUniform("windX");					glUniform1f(shadersGroup[0]("windX"), parameters->Wind.x);
	shadersGroup[0].AddUniform("windY");					glUniform1f(shadersGroup[0]("windY"), parameters->Wind.y);
	shadersGroup[0].AddUniform("windZ");					glUniform1f(shadersGroup[0]("windZ"), parameters->Wind.z);
	shadersGroup[0].UnUse();

	shadersGroup[1].LoadFromFile(GL_VERTEX_SHADER, "shaders/textureMappingAndPhongLight.vert");
	shadersGroup[1].LoadFromFile(GL_FRAGMENT_SHADER, "shaders/textureMappingAndPhongLight.frag");
	shadersGroup[1].CreateAndLinkProgram();
	shadersGroup[1].Use();
	
	shadersGroup[1].AddUniform("widthInterval");			glUniform1f(shadersGroup[1]("widthInterval"), model->clothWidth - 1);
	shadersGroup[1].AddUniform("heightInterval");			glUniform1f(shadersGroup[1]("heightInterval"), model->clothHeight - 1);
	shadersGroup[1].AddUniform("tex");						glUniform1i(shadersGroup[1]("tex"), 2);
	shadersGroup[1].AddUniform("cameraPosition");			glUniform3f(shadersGroup[1]("cameraPosition"), -10.0, 10.0, 10.0);
	shadersGroup[1].AddUniform("lightColor");				glUniform3f(shadersGroup[1]("lightColor"), parameters->LightColor.x, parameters->LightColor.y, parameters->LightColor.z);

	shadersGroup[1].UnUse();
}

void Shaders::bindModel(Model *model) {
	this->model = model;
}

void Shaders::bindParameters(Parameters *parameters) {
	this->parameters = parameters;
}