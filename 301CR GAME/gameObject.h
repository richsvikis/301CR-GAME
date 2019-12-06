#pragma once
#pragma once
/* OPENGL_INCLUDES */
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif 

# include <glm.hpp> 
# include <map>
#include "Collider.h"
#include <map>


class gameObject
{
protected:
	unsigned int base;


public:
	static std::map <int, bool> specialKeys;
	static std::map <char, bool> keys;
	Collider* collider = NULL;

	glm::vec3 heading = glm::vec3(0.0, 0.0, -1.0);  ///<Current heading (direction) the GameObject is facing.


	glm::vec3 position;
	gameObject(glm::vec3 position);
	//	~gameObject();

	virtual unsigned int setupDrawing(unsigned int listBase);
	virtual void drawScene(); ///Function to perform this object's part of the redraw work. The default version in GameObject will put the object in the right place and redraw it. This can be overridden.

							  /* Every GameObject must implement the following pure virtual function or otherwise cause a compile error.*/
	virtual void start() = 0; ///<Pure virtual start function, run once when the engine starts.  Must override in inherited classes.
	virtual void update(int deltaTime) = 0;
	virtual void collides(Collider* other);///<Pure virtual update function, run periodicity to update the game state. Must override in inherited classes.
};


