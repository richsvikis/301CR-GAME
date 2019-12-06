#include "Model1.h"
#include "CubeCollider.h"



Sun::Sun()
{
}

Sun::Sun(glm::vec3 Position)
{
	LoadModel("Models/Sun.obj");

	position = Position;
	collider = new CubeCollider(&this->position, 1, 1, 1);
}

void Sun::drawSun(glm::mat4 model, GLuint uniformModel)
{
	model = glm::mat4{ 1.0 };
	model = glm::translate(model, glm::vec3(position));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::rotate(model, sunRot, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	RenderModel();
}


void Sun::collides(Collider* other)
{
}

void Sun::update()
{
	sunRot += 0.01f;
	if (sunRot > 360)
	{
		sunRot = 0;
	}
}

Sun::~Sun()
{
}
