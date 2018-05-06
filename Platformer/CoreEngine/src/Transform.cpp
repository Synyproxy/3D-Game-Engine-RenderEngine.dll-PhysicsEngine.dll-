#include "stdafx.h"

#include <Transform.h>

using namespace CoreEngineNS;

Transform::Transform() : m_position{glm::vec3(0, 0, 0)}, m_scale {glm::vec3(1, 1, 1)}
{
}

Transform::~Transform()
{
}

const glm::vec3& Transform::GetPosition() const
{
	return m_position;
}

void Transform::SetPosition(const glm::vec3& p_position)
{
	m_position = p_position;
}

void Transform::SetPositionX(const float& p_x)
{
	m_position = glm::vec3(p_x, m_position.y, m_position.z);
}

void Transform::SetPositionY(const float& p_y)
{
	m_position = glm::vec3(m_position.x, p_y, m_position.z);
}

void Transform::SetPositionZ(const float& p_z)
{
	m_position = glm::vec3(m_position.x, m_position.y, p_z);
}

const glm::vec3& Transform::GetScale() const
{
	return m_scale;
}

void Transform::SetScale(const glm::vec3& p_scale)
{
	m_scale = p_scale;
}
