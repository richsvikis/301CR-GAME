#pragma once

#include "gameObject.h"


class Pockets : public gameObject
{
private:
public:
	Pockets(glm::vec3 pos);
	~Pockets();
	unsigned int setupDrawing(unsigned int listBase);
	void start();
	void update(int deltaTime);
};