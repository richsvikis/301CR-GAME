


#pragma once
#include "gameObject.h"
# include <glm/glm.hpp> 
#include <cmath>
#include<glm/gtx/rotate_vector.hpp>
#define TURNING_SPEED 100.0 //<turning speed in degrees per second
#define MOVE_SPEED 40.0 //<move speed in coordinate units per second

class Character : public gameObject
{
private:

	unsigned int base;
public:

	glm::vec3 position;
	glm::vec3 startingHeading = heading;
	float rotationAngle = 10;
	float pitchAngle = 5;

	Character(glm::vec3 position);
	~Character();
	void drawScene();
	void start();
	void update(int deltaTime);
	//void collides(Collider* other);
	unsigned int setupDrawing(unsigned int listbase);

};

