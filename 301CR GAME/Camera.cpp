#include "camera.h"


Camera::Camera()
{
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMovementSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(-15.0f, 5.0f, -5.0f);

	movementSpeed = startMovementSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	if (keys[GLFW_KEY_W])
	{
		position += front * movementSpeed * deltaTime;
	}


	if (keys[GLFW_KEY_S])
	{
		position -= front * movementSpeed * deltaTime;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * movementSpeed * deltaTime;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * movementSpeed * deltaTime;
	}
}

void Camera::mouseControl(GLfloat changeX, GLfloat changeY)
{
	changeX = changeX * turnSpeed;
	changeY = changeY * turnSpeed;

	yaw += changeX;
	pitch += changeY;

	if (pitch > 50.0f)
	{
		pitch = 50.0f;
	}

	if (pitch < -50.0f)
	{
		pitch = -50.0f;
	}

	if (yaw > 360)
	{
		yaw = 0;
	}

	if (yaw < 0)
	{
		yaw = 360;
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCamPosition()
{
	return position;
}

glm::vec3 Camera::getCamDirection()
{
	return glm::normalize(front);
}

Camera::~Camera()
{
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));

}





/*

#include "Camera.h"

#include "Matrix.h"

Camera::Camera(const Config& config) noexcept
	: m_config(config)
{
	m_projectionMatrix = makeProjectionMatrix(config);

	position = { 0, 0, -3.5 };
}

void Camera::update() noexcept
{
	position = { m_pEntity->position.x, m_pEntity->position.y + 0.6f, m_pEntity->position.z };
	rotation = m_pEntity->rotation;

	m_viewMatrix = makeViewMatrix(*this);
	m_projViewMatrx = m_projectionMatrix * m_viewMatrix;
	m_frustum.update(m_projViewMatrx);
}

void Camera::hookEntity(const Entity& entity) noexcept
{
	m_pEntity = &entity;
}

const glm::mat4& Camera::getViewMatrix() const noexcept
{
	return m_viewMatrix;
}

const glm::mat4& Camera::getProjMatrix() const noexcept
{
	return m_projectionMatrix;
}

const glm::mat4& Camera::getProjectionViewMatrix() const noexcept
{
	return m_projViewMatrx;
}

const ViewFrustum& Camera::getFrustum() const noexcept
{
	return m_frustum;
}

*/