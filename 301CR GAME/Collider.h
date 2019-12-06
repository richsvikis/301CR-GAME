#pragma once
#include <GL/glew.h>
//#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

class Collider
{
public:
	virtual bool collidesWith(Collider* other) = 0;
	virtual float minX() = 0;
	virtual float minY() = 0;
	virtual float minZ() = 0;
	virtual float maxX() = 0;
	virtual float maxY() = 0;
	virtual float maxZ() = 0;

	glm::vec3* colliderCentre = NULL;
};

