#include "stdafx.h"

#include <Transform.h>

using namespace CoreEngineNS;

Transform::Transform() : m_position{Vec2(0, 0)}
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

const Vec2& Transform::GetPosition() const
{
	return m_position;
}

void Transform::SetPosition(const Vec2& p_position)
{
	m_position = p_position;
}
