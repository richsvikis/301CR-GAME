#pragma once
#include <glm.hpp>
#include <glew.h>


class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity);

	~Light();

protected:
	glm::vec3 colour;
	GLfloat ambientIntensity;

	GLfloat diffuseIntensity;
};

