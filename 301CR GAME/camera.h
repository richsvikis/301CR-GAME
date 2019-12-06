#pragma once

#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <glfw3.h>
#include <string>




class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMovementSpeed, GLfloat startTurnSpeed);

	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat changeX, GLfloat changeY);

	glm::mat4 calculateViewMatrix();

	glm::vec3 getCamPosition();
	glm::vec3 getCamDirection();

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat movementSpeed;
	GLfloat turnSpeed;

	void update();
};





/*

#include <glm/glm.hpp>
#include "Frustum.h"
#include "Entity.h"
#include "Config.h"

class Camera : public Entity
{
public:
	Camera(const Config& config) noexcept;

	void update() noexcept;
	void hookEntity(const Entity& entity) noexcept;

	const glm::mat4& getViewMatrix()           const noexcept;
	const glm::mat4& getProjMatrix()           const noexcept;
	const glm::mat4& getProjectionViewMatrix() const noexcept;

	const ViewFrustum& getFrustum() const noexcept;

private:
	const Entity* m_pEntity;

	ViewFrustum m_frustum;

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projViewMatrx;

	Config m_config;


};


*/