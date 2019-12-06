#include "Character.h"
//#include "CubeCollider.h"
//#include "Collider.h"

Character::Character(glm::vec3 pos) :gameObject(pos) {
//	Character::collider = new CubeCollider(&this->position, 1.5, 5, 1.5);
}

Character::~Character() {
//	delete Character::collider;
//	Character::collider = NULL;
}



void Character::drawScene()
{


	//movement
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(this->position.x, this->position.y, this->position.z);
	glRotatef(0.5, 50, 50, 50);
	glutSolidCone(0.3, 1.0, 40, 10);



	
	//White Ball
	glPushMatrix();
	glTranslatef(0.7, 0.2, -0.3);
	glColor3f(6, 4, 8);
	glutSolidSphere(2, 40, 50);
	glPopMatrix();
	






	//rotate openGL object
	glRotatef(pitchAngle, 5.0, 5.0, 5.0);
	glRotatef(rotationAngle, 3.0, 3.0, 3.0);
	glCallList(this->base); // Draw Hovercraft.
	glPopMatrix();
	glPopMatrix();
}


void Character::start()
{
}




void Character::update(int deltaTime) {
	float moveStep = MOVE_SPEED * (deltaTime / 1000.0); //movement speed in units per second * deltaTime in sec = moveStep
	float turningSpeed = TURNING_SPEED * (deltaTime / 1000.0); //turning speed (degrees/sec) * deltaTime in sec = turning speed over delta time

	if (specialKeys[GLUT_KEY_DOWN]) {
		this->position += this->heading * moveStep;
	}
	if (specialKeys[GLUT_KEY_PAGE_UP]) {
		this->pitchAngle += turningSpeed; //in degrees not radians
	}
	if (specialKeys[GLUT_KEY_PAGE_DOWN]) {
		this->pitchAngle -= turningSpeed; //in degrees not radians
	}

	if (specialKeys[GLUT_KEY_LEFT]) {
		this->rotationAngle += turningSpeed; //in degrees not radians
	}
	if (specialKeys[GLUT_KEY_UP]) {
		this->position -= this->heading * moveStep;
	}
	if (specialKeys[GLUT_KEY_RIGHT]) {
		this->rotationAngle -= turningSpeed; //in degrees not radians
	}

	//rotate the heading
	//In the drawscene we will need to rotate by the full rotation since the start
	//Therfore we start heard from the original startingheading, so that we can use the same variables for the rotations
	this->heading = glm::rotate(this->startingHeading, glm::radians(rotationAngle), glm::vec3(0.0, 1.0, 0.0));
	this->heading = glm::rotate(this->heading, glm::radians(pitchAngle), glm::vec3(0.0, 0.0, 1.0));
}




unsigned int Character::setupDrawing(unsigned int listBase)
{
	this->base = ++listBase;
	//glNewList(this->base, GL_COMPILE);
	glPushMatrix();
	glColor3f(-2, 0, 2);
	//glTranslatef(-2, 0, 2);
	glRotatef(-200, 0, 1, 0);
	glutSolidCone(0.7, 0.8, 20, 20);
	glPushMatrix();
	glTranslatef(5, 10, -10);
	glColor3f(3, 3, 5);
	glutSolidCube(0.8);
	glPopMatrix();
	glPopMatrix();
	return this->base;
}
//void Character::collides(Collider* other) {
	//if (debugMode) {
	//	std::cout << "Hovercraft collides!" << std::endl;
	//}
