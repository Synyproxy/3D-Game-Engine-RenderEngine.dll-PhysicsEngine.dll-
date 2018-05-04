#include "stdafx.h"

#include <Camera.h>

using namespace RenderEngineNS;

Camera::Camera(
	const glm::vec3 p_position,
	const glm::vec3 p_up,
	const float p_yaw,
	const float p_pitch
) : m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_movementSpeed(SPEED),
m_mouseSensitivity(SENSITIVITY),
m_zoom(ZOOM)
{
	m_position = p_position;
	m_worldUp = p_up;
	m_yaw = p_yaw;
	m_pitch = p_pitch;
	UpdateCameraVectors();
}

Camera::Camera(
	const float p_posX, const float p_posY, const float p_posZ,
	const float p_upX, const float p_upY, const float p_upZ,
	const float p_yaw, const float p_pitch
) : m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
m_movementSpeed(SPEED),
m_mouseSensitivity(SENSITIVITY),
m_zoom(ZOOM)
{
	m_position = glm::vec3(p_posX, p_posY, p_posZ);
	m_worldUp = glm::vec3(p_upX, p_upY, p_upZ);
	m_yaw = p_yaw;
	m_pitch = p_pitch;
	UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::ProcessKeyboard(const Camera_Movement p_direction, const float p_deltaTime)
{
	const float velocity = m_movementSpeed * p_deltaTime;
	if (p_direction == FORWARD)
		m_position += m_front * velocity;
	if (p_direction == BACKWARD)
		m_position -= m_front * velocity;
	if (p_direction == LEFT)
		m_position -= m_right * velocity;
	if (p_direction == RIGHT)
		m_position += m_right * velocity;
}

void Camera::ProcessMouseMovement(float p_xoffset, float p_yoffset, const GLboolean p_constrainPitch)
{
	p_xoffset *= m_mouseSensitivity;
	p_yoffset *= m_mouseSensitivity;

	m_yaw += p_xoffset;
	m_pitch += p_yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (p_constrainPitch)
	{
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(const float p_yoffset)
{
	if (m_zoom >= 1.0f && m_zoom <= 45.0f)
		m_zoom -= p_yoffset;
	if (m_zoom <= 1.0f)
		m_zoom = 1.0f;
	if (m_zoom >= 45.0f)
		m_zoom = 45.0f;
}

void Camera::UpdateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);

	// Also re-calculate the Right and Up vector
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));

	// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_up = glm::normalize(glm::cross(m_right, m_front));
}
