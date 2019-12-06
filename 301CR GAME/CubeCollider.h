#pragma once
#include "Collider.h"
class CubeCollider :
	public Collider
{
public:
	CubeCollider();
	CubeCollider(glm::vec3* centre, float cubeWidth, float cubeHeight, float cubeLength);

	float minX();
	float minY();
	float minZ();
	float maxX();
	float maxY();
	float maxZ();

	float length = 0.0, width = 0.0, height = 0.0;

	bool collidesWith(Collider* other);

	~CubeCollider();
};

