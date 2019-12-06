#pragma once
/* OPENGL_INCLUDES */
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif 
# include <glm/glm.hpp> 
#include <iostream>
#include "gameObject.h"

//bool gameObject::debugMode;


unsigned int gameObject::setupDrawing(unsigned int listBase)
{
	return 0;
}

void gameObject::drawScene()
{

	//if (debugMode) {
	//	//Display the collider bounding box.
	//	this->collider->Draw();
	//}
}

gameObject::gameObject(glm::vec3 position)
{

}

//void gameObject::collides(Collider* other) {
//}