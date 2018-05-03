#include "stdafx.h"

#include <Transform.h>

using namespace CoreEngineNS;

Transform::Transform() : m_position{glm::vec3(0, 0, 0)}, m_scale {glm::vec3(1, 1, 1)}
{
}

Transform::~Transform()
{
}

void Transform::Awake()
{

}

void Transform::Update()
{

}

void Transform::Draw()
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

const glm::vec3& Transform::GetScale() const
{
	return m_scale;
}

void Transform::SetScale(const glm::vec3& p_scale)
{
	m_scale = p_scale;
}
