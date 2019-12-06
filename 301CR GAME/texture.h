#pragma once

#include <GL\glew.h>
#include <string>
#include "Val.h"

class Texture
{
public:
	Texture();
	Texture(const char* fileLoc);

	bool loadTexture();
	bool loadTextureA();

	void useTexture();
	void clearTexture();

	~Texture();
private:
	GLuint textureID;
	int width, height, bitDepth;

	const char* fileLocation;
};

